#include "DistanceUS.h"

DistanceUS us (2,3,5,93);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(us.read());
}
