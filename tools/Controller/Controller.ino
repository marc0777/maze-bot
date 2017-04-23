#include "Motion.h"

Motion mot;
byte data;

void setup() {
  Serial3.begin(9600);
  Serial3.println("Pronto ad inviare");
}

void loop() {
    if (Serial3.available() > 0) {
      data=Serial3.read()-'0';
      Serial3.print("Invio dati: ");
      Serial3.println(data);
      mot.set(data);
    }
}
