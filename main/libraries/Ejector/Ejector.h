#ifndef EJECTOR_H
#define EJECOR_H

#include <Arduino.h>

#define PIN1 6
#define PIN2 7

#define DELAY 869.56
#define MINDEL 200

class Ejector {
  public :
    Ejector(int ntappi);
    void eject();
    bool isEmpty();
    void turnOut();
    void turnIn();
    void stop();
  private :
    byte kits;
};

Ejector::Ejector(int ntappi) {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);

  digitalWrite(PIN1, 0);
  digitalWrite(PIN2, 0);

  kits = ntappi;
}

void Ejector::eject() {
  digitalWrite(PIN2, 1);
  delay(DELAY);
  digitalWrite(PIN2, 0);
  delay(MINDEL);
  digitalWrite(PIN1, 1);
  delay(MINDEL);
  digitalWrite(PIN1, 0);
  delay(MINDEL);
  digitalWrite(PIN2, 1);
  delay(MINDEL);
  digitalWrite(PIN2, 0);
  kits--;
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

#endif
