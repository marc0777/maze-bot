#ifndef DistanceUS_h
#define DistanceUS_h

#include <Arduino.h>

#define DIVISOR 58.0

class DistanceUS {
  public:
    DistanceUS(int trigPin, int echoPin, int average, int tolerance);
    float read();
  private:
    float cm();
    int trigPin;
    int echoPin;
    int irPin;
    int average;
    int tolerance;
    float previousDistance;
};
#endif
