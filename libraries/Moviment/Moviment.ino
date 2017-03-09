#include "Moviment.h"

Moviment mov = Moviment (120,0,0);

void setup() {
}

void loop() {
  mov.go();
  delay(10000);
  mov.rotate(false);
  delay(10000);
}
