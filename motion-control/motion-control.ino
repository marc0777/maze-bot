#include <Arduino.h>
#include <Wire.h>
#include <Moviment.h>
#include <IMU.h>
#include <PID.h>

#define ADDRESS 7
#define OUT_MIN 100
#define OUT_MAX 255

double Setpoint=inputPID=outputPID=0;//copiato dall'esempio della libreria del PID
double Kp=2, Ki=5, Kd=1;//valori di default del PID da mettere a posto
PID pid(&inputPID, &outputPID, &Setpoint, Kp, Ki, Kd, DIRECT);  //inizializzazione dell'oggetto PID copiato senza capire cos'è il DIRECT
                                                            //che non è stato trovato da nessuna parte, ma stranamente compila
                                                            //l'input e l'output sono le variabili dove bisognerà assegnare il valore
                                                            //letto il Setpoint è la variabile di riferimento, le tre costanti sono i
                                                            //parametri da mettere apposto.


float rapportoVR = 60 / 90; //deltaV/deltaR
float direzione = 0;
byte state = 0;

Moviment mov(100, 0, 0);
IMU orientation;

void receiveEvent(int howMany) {
  state = Wire.read();
  switch (state) {
    case 0:
      mov.stop();
      break;
    case 1:
      goStraight(false);
      break;
    case 2:
      mov.rotate(false);
      break;
    case 3:
      goStraight(true);
      break;
    case 4:
      mov.rotate(true);
      break;
  }
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
  while(state==1) {
    direzione = orientation.yaw();
    if (direzione < 0) mov.setK(-direzione * 2, 0);
    else if (direzione > 0) mov.setK(0, direzione * 2);
  }
}

void goStraightPID(bool invert) {
  orientation.start();
  mov.go(invert);
  while(state==1) {
    direzione = orientation.yaw();
    inputPID=direzione;
    pid.Conpute();
    if (direzione < 0) mov.setK(outputPID, -outputPID);
    else if (direzione > 0) mov.setK(-outputPID,pitoutPID);
  }
}

float endAngle(float n, bool s) {
  if (s) {
    n += 90;
    return (n > 360)?n-360:n;
  }
  else {
    n -= 90;
    return (n < 0)?n+360:n;
  }
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  orientation.begin();
  delay(100);
  orientation.calibrate();
  delay(100);
  pid.SetOutputLimits(OUT_MIN,OUT_MAX);
}

void loop() {
}
