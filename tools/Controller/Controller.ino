#include "Motion.h"


int inclination;
bool turning = false;

Motion mot(&turning);

byte data;

void receiveEvent(int howMany) {
  byte data = Wire.read();
  if (data == 255) turning=false;
  else inclination = data-90;
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
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
