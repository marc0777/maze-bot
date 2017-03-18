#include <Arduino.h>

#include "DistanceIR.h"

DistanceIR dist(A0, 25, 93);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(dist.read());
}
