#include <Arduino.h>

#include "DistanceUS.h"

DistanceUS us1 (40, 42, 5, 93);
DistanceUS us2 (36, 38, 5, 93);
DistanceUS us3 (32, 34, 5, 93);
DistanceUS us4 (28, 30, 5, 93);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(" Frontr: ");
  Serial.print(us1.read());
  Serial.print("\t");
  Serial.print(" Frontl: ");
  Serial.print(us2.read());
  Serial.println("\t");
//  Serial.print(" Rigth: ");
//  Serial.print(us3.read());
//  Serial.print("\t");
//  Serial.print(" Left: ");
//  Serial.print(us4.read());
//  Serial.print(" Differenza: ");
//  Serial.println(us1.read()-us2.read());
  delay(500);
}
