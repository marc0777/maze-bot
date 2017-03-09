#include "ColorIR.h"

ColorIR color;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(color.read());
}
