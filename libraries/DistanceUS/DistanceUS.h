#ifndef DistanceUS_h
#define DistanceUS_h

#include <Arduino.h>

#define DIVISOR 58.0

class DistanceUS {
  public:
    DistanceUS(byte trigPin, byte echoPin, byte average, byte tolerance);
    float read();
  private:
    float cm();
    byte trigPin;
    byte echoPin;
    byte average;
    byte tolerance;
    float previousDistance;
};
#endif
