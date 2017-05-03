#include "Ejector.h"

Ejector::Ejector(int ntappi) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  kits = ntappi;
}

void Ejector::eject() {
  digitalWrite(PIN1, 1);
  delay(DELAY);
  digitalWrite(PIN1, 0);  
  delay(MINDEL);
  digitalWrite(PIN2, 1);
  delay(MINDEL);
  digitalWrite(PIN2, 0);
  delay(MINDEL);  
  digitalWrite(PIN1, 1);
  delay(MINDEL);
  digitalWrite(PIN1, 0);
  
  kits --;  
}

bool Ejector::isEmpty() {
  return kits < 1;
}

