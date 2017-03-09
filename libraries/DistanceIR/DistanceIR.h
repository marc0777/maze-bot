#ifndef DistanceIR_h
#define DistanceIR_h

#include "Arduino.h"

class DistanceIR
{
  public:
    DistanceIR (int irPin, int avg, int tolerance);
    float read();
  private:
    float cm();
    int irPin;
    int average;
    int tolerance;
    float previousDistance;
};
#endif
