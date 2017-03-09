#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
  public:
    Motor(byte e, byte i1, byte i2);
    void start(byte power, bool inverse);
    void stop();
  private:
    byte inverter1, inverter2, enable;
};
#endif
