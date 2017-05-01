#include <Arduino.h>

#include "DistanceUS.h"

DistanceUS us1 (40, 42);
DistanceUS us2 (36, 38);
DistanceUS us3 (32, 34);
DistanceUS us4 (28, 30);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(" Frontr: ");
  Serial.print(us1.read());
  Serial.print("\t");
  Serial.print(" Frontl: ");
  Serial.print(us2.read());
  Serial.print("\t");
  Serial.print(" Rigth: ");
  Serial.print(us3.read());
  Serial.print("\t");
  Serial.print(" Left: ");
  Serial.println(us4.read());
  delay(500);
}
