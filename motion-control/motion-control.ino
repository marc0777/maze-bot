#include <Arduino.h>
#include "MadgwickAHRS.h"
#include <Wire.h>
#include <Moviment.h>

#define ADDRESS 7

float rapportoVR=60/90;//deltaV/deltaR
byte state = 0;
Madgwick filter;
Moviment mov(100,0,0);

void receiveEvent(int howMany) {
  state = Wire.read();
  mov.set(state);
}

void requestEvent() {
  Wire.write(mov.get());
}

void rotationSpeed(bool direction , float endRotation){
  if(direction)mov.setK(40+((endRotation-filter.getYaw())*rapportoVR),40+((endRotation-filter.getYaw())*rapportoVR));
  else mov.setK(40+((filter.getYaw()-endRotation)*rapportoVR),40+((filter.getYaw()-endRotation)*rapportoVR));
}// negare la condizione se il filtro funziona in modo diverso

float endAngle(float n, bool s){
  if(s){
    n+=90;
    if(n>360)return n-360;
    else return n;
  }
  else {
    n-=90;
    if(n<0)return n+360;
    else return n;
  }
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {

}
