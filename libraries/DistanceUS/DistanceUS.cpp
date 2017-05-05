#include "DistanceUS.h"

DistanceUS::DistanceUS(byte trigPin, byte echoPin, byte average, byte tolerance) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  this->average = average;
  this->tolerance = tolerance;
}

float DistanceUS::cm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, 100000) / DIVISOR;
}

float DistanceUS::read() {
  int p = 0;
  float sum = 0;
  float temp;
  for (int i = 0; i < average; i++) {
    temp = cm();
    if (temp >= ((tolerance / 100) * previousDistance)) {
      previousDistance = temp;
      sum = sum + temp;
      p++;
    }
  }
  return sum / p;
}