#include <Wire.h>
#include <Moviment.h>
#include <IMU.h>
#include <PID.h>

#define MASTER_ADDRESS 8
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
byte state = 255;
byte requested = 255;
byte prevState = 255;
int inclination;

Moviment mov(120, 0, 0);
IMU orientation;

void receiveEvent(int howMany) {
  byte input = Wire.read();
  if (input < 200) state = input;
  else if (input == 255) requested = 0;
  else mov.setSpeed((input-200)*5);
}

void send(byte data, byte address) {
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();
}

void answer() {
  if (requested!=255)
    inclination=orientation.pitch();
    send(inclination+90,MASTER_ADDRESS);
    requested=255;
  }
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
    answer();
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
    answer();
  }
}

void turn(bool invert) {
  orientation.start();
  mov.rotate(invert);
  float end = endAngle(orientation.yaw(), invert);
  if (invert) while(orientation.yaw()<end) rotationSpeed(invert,end);
  else while(orientation.yaw()>end) rotationSpeed(invert,end);
  mov.setK(0,0);
  mov.stop();
  state=0;
  send(255,MASTER_ADDRESS);
}

float endAngle(float angle, bool invert) {
  if (invert) {
    angle += 90;
    return (angle > 360) ? angle - 360 : angle;
  }
  else {
    angle -= 90;
    return (angle < 0) ? angle + 360 : angle;
  }
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  orientation.begin();
  delay(100);
  orientation.calibrate();
  delay(100);
  orientation.start();
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
  answer();

}
