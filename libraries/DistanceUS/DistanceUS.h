#ifndef DistanceUS_h
#define DistanceUS_h

#include <Arduino.h>

#define DIVISOR 58.0

class DistanceUS {
  public:
    DistanceUS(int trigPin, int echoPin);
    float read();
  private:
    byte trigPin;
    byte echoPin;
};
#endif
