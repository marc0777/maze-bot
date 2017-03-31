#include "Color.h"

Color c;
void setup() {
 Serial.begin(9600);
}

void loop() {
  Serial.println("LEGGO");
  Serial.println(c.read());
  delay(1000);
}
