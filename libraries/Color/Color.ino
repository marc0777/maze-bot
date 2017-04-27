#include "Color.h"

Color *color;

void setup() {
  Serial.begin(9600);
  color = new Color();
}
//@return 0 se sotto non c'è niente, 1 se c'è uno specchio e 2 se è nero.
void loop() {
  Serial.println("LEGGO");
  byte col = color->read();
  Serial.println(col);
  switch(col) {000
    case 0:
      Serial.println("bianco");
      break;
    case 1:
      Serial.println("specchio");
      break;
    case 2:
      Serial.println("nero");
      break;
  }
  delay(1000);
}
