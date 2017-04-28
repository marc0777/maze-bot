#include "Motion.h"

Motion mot;
byte data;

void setup() {
  Serial.begin(9600);
  Serial.println("Pronto ad inviare");
}

void loop() {
    if (Serial.available() > 0) {
      data=Serial.read()-'0';
      Serial.print("Invio dati: ");
      Serial.println(data);
      mot.set(data);
    }
}
