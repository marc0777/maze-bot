#include "DistanceUS.h"

DistanceUS::DistanceUS(int trigPin, int echoPin) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  this->trigPin = trigPin;
  this->echoPin = echoPin;
}

float DistanceUS::read() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, 100000) / DIVISOR;
}
