#include "Arduino.h"
#include "DistanceIR.h"

DistanceIR::DistanceIR(int irPin, int average, int tolerance) {
  this->irPin = irPin;
  this->average = average;
  this->tolerance = tolerance / 100;
  pinMode(irPin, INPUT);
}

float DistanceIR::cm() {
  float voltFromRaw = map(analogRead(irPin), 0, 1023, 0, 5000);
  return 27.728 * pow(voltFromRaw / 1000, -1.2045);
}

float DistanceIR::read() {
  int p = 0;
  float sum = 0;
  float temp;
  for (int i = 0; i < average; i++) {
    temp = cm();
    if (temp >= (tolerance * previousDistance)) {
      previousDistance = temp;
      sum = sum + temp;
      p++;
    }
  }
  return sum / p;
}
