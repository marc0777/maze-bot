#include <Arduino.h>

#include "Temperature.h"

Temperature t = Temperature(0x5A);

void setup() {
  Serial.begin(9600);
  t.begin();
}

void loop() {
  Serial.println(t.readObj());
}
