#include <Arduino.h>
#include <Wire.h>
#include <Moviment.h>
#include <IMU.h>

#define ADDRESS 7
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

float endAngle(float n, bool s) {
  if (s) {
    n += 90;
    if (n > 360)return n - 360;
    else return n;
  }
  else {
    n -= 90;
    if (n < 0)return n + 360;
    else return n;
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
}

void loop() {
}
