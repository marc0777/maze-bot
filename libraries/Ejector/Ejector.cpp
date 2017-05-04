#include "Ejector.h"

Ejector::Ejector(int ntappi) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  digitalWrite(PIN1, 0);
  digitalWrite(PIN2, 0);
  digitalWrite(ENABLE, 1);

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

void Ejector::turnOut() {
  digitalWrite(PIN2, 0);
  digitalWrite(PIN1, 1);
}

void Ejector::turnIn() {
  digitalWrite(PIN1, 0);
  digitalWrite(PIN2, 1);
}

void Ejector::stop() {  
  digitalWrite(PIN1, 0);
  digitalWrite(PIN2, 0);
  
}

