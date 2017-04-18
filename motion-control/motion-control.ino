#include <Arduino.h>
#include <Wire.h>
#include <Moviment.h>
#include <IMU.h>
#include <PID.h>

#define ADDRESS 7
#define OUT_MIN 100
#define OUT_MAX 255

#define Kp 2
#define Ki 5
#define Kd 1

double Setpoint, inputPID, outputPID; //copiato dall'esempio della libreria del PID
PID pid(&inputPID, &outputPID, &Setpoint, Kp, Ki, Kd, DIRECT);  //inizializzazione dell'oggetto PID copiato senza capire cos'è il DIRECT
//che non è stato trovato da nessuna parte, ma stranamente compila
//l'input e l'output sono le variabili dove bisognerà assegnare il valore
//letto il Setpoint è la variabile di riferimento, le tre costanti sono i
//parametri da mettere apposto.


float rapportoVR = 60 / 90; //deltaV/deltaR
float direzione = 0;
byte state = -1;
byte prevState = -1;

Moviment mov(255, 0, 0);
IMU orientation;

void receiveEvent(int howMany) {
  state = Wire.read();
}


void requestEvent() {
  Wire.write(state);
}

void rotationSpeed(bool direction , float endRotation) {
  direzione = orientation.yaw();
  if (direction) mov.setK(40 + ((endRotation - direzione)*rapportoVR), 40 + ((endRotation - direzione)*rapportoVR));
  else mov.setK(40 + ((direzione - endRotation)*rapportoVR), 40 + ((direzione - endRotation)*rapportoVR));
}// negare la condizione se il filtro funziona in modo diverso

void goStraight(bool invert) {
  orientation.start();
  mov.go(invert);
  while (state == 1 || state == 3) {
    direzione = orientation.yaw();
    if (direzione < 0) mov.setK(-direzione * 2, 0);
    else if (direzione > 0) mov.setK(0, direzione * 2);
  }
}

void goStraightPID(bool invert) {
  orientation.start();
  mov.go(invert);
  while (state == 1 || state == 3) {
    direzione = orientation.yaw();
    inputPID = direzione;
    pid.Compute();
    if (direzione < 0) mov.setK(outputPID, -outputPID);
    else if (direzione > 0) mov.setK(-outputPID, outputPID);
  }
}

void turn(bool invert) {
  orientation.start();
  mov.rotate(invert);
  float end = endAngle(orientation.yaw(), invert);
  if (invert) while(orientation.yaw()<end);
  else while(orientation.yaw()>end);
  mov.stop();
}

float endAngle(float angle, bool invert) {
  if (invert) {
    angle += 50;
    return (angle > 360) ? angle - 360 : angle;
  }
  else {
    angle -= 50;
    return (angle < 0) ? angle + 360 : angle;
  }
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  //Wire.onRequest(requestEvent);
  orientation.begin();
  delay(100);
  orientation.calibrate();
  delay(100);
  pid.SetOutputLimits(OUT_MIN, OUT_MAX);
}

void loop() {
  if (state!=prevState) {
    switch (state) {
    case 0:
      mov.stop();
      break;
    case 1:
      goStraightPID(false);
      break;
    case 2:
      turn(false);
      break;
    case 3:
      goStraightPID(true);
      break;
    case 4:
      turn(true);
      break;
    case 5:
      mov.rotate(false);
      break;
    case 6:
      mov.rotate(true);
      break;
    }
    prevState=state;
  }
}
