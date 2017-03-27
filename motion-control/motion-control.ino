#include <Arduino.h>
#include <MadgwickAHRS.h>
#include <Wire.h>
#include <Moviment.h>
#include <L3G4200D.h>
#include <ADXL345.h>

#define ADDRESS 7
#define REFRESH 50

const unsigned long microsPerReading = 1000000 / REFRESH;
unsigned long microsPrevious;
float rapportoVR = 60 / 90; //deltaV/deltaR
float direzione = 0;
byte state = 0;

Moviment mov(100, 0, 0);
L3G4200D gyroscope;
ADXL345 acc;
Madgwick filter;

void receiveEvent(int howMany) {
  state = Wire.read();
  mov.set(state);
}

void requestEvent() {
  Wire.write(mov.get());
}


void rotationSpeed(bool direction , float endRotation) {
  if (direction)mov.setK(40 + ((endRotation - filter.getYaw())*rapportoVR), 40 + ((endRotation - filter.getYaw())*rapportoVR));
  else mov.setK(40 + ((filter.getYaw() - endRotation)*rapportoVR), 40 + ((filter.getYaw() - endRotation)*rapportoVR));
}// negare la condizione se il filtro funziona in modo diverso

void goStraight(bool invert, float dritto) {
  start();
  while(state==1) {
    unsigned long microsNow;
    microsNow = micros();
    if (microsNow - microsPrevious >= microsPerReading) update();
    direzione = filter.getYaw();
    if (direzione < dritto)mov.setK((dritto - direzione) * 2, 0);
    else if (direzione > dritto)mov.setK(0, (direzione - dritto) * 2);
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

void begin() {
  gyroscope.begin(L3G4200D_SCALE_250DPS, L3G4200D_DATARATE_100HZ_12_5);
  acc.begin();
}

void calibrate() {
  gyroscope.calibrate(255);
}

void start() {
  filter.begin(REFRESH);
  microsPrevious = micros();
}

void update() {
  acc.read();
  gyroscope.read();
  filter.update(gyroscope.x, gyroscope.y, gyroscope.z, acc.x, acc.y, acc.z);
  microsPrevious+=microsPerReading;
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  begin();
  delay(100);
  calibrate();
  delay(100);
}

void loop() {
}
