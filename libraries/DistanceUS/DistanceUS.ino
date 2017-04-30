#include <Arduino.h>

#include "DistanceUS.h"

DistanceUS us1 (40, 42);
DistanceUS us2 (36, 38);
DistanceUS us3 (32, 34);
DistanceUS us4 (28, 30);

void setup() {
  Serial3.begin(9600);
}

void loop() {
  Serial3.print(" Frontr: ");
  Serial3.print(us1.read());
  Serial3.print("\t");
  Serial3.print(" Frontl: ");
  Serial3.print(us2.read());
  Serial3.print("\t");
  Serial3.print(" Rigth: ");
  Serial3.print(us3.read());
  Serial3.print("\t");
  Serial3.print(" Left: ");
  Serial3.println(us4.read());
  delay(500);
}
