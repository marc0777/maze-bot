#include <Arduino.h>
#include "MadgwickAHRS.h"
#include <Wire.h>
#include <Moviment.h>

#define ADDRESS 7

float rapportoVR = 60 / 90; //deltaV/deltaR
float direzione = 0;
byte state = 0;
Madgwick filter;
Moviment mov(100, 0, 0);

void receiveEvent(int howMany) {
  state = Wire.read();
  mov.set(state);
  for (int i = 0; i < state; i++) {
    digitalWrite(13, 1);
    delayMicroseconds(500000);
    digitalWrite(13, 0);
    delayMicroseconds(500000);
  }
}

void requestEvent() {
  Wire.write(mov.get());
}

void rotationSpeed(bool direction , float endRotation) {
  if (direction)mov.setK(40 + ((endRotation - filter.getYaw())*rapportoVR), 40 + ((endRotation - filter.getYaw())*rapportoVR));
  else mov.setK(40 + ((filter.getYaw() - endRotation)*rapportoVR), 40 + ((filter.getYaw() - endRotation)*rapportoVR));
}// negare la condizione se il filtro funziona in modo diverso

void goStraight(bool invert, float dritto) {
  direzione = filter.getYaw();
  if (direzione < dritto)mov.setK((dritto - direzione) * 2, 0);
  else if (direzione > dritto)mov.setK(0, (direzione - dritto) * 2);
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
}

void loop() {

}
