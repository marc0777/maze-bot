#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
  public:
    Motor(byte e, byte i1, byte i2);
    void start(byte speed, bool inverse);
    void setSpeed(byte speed);
    void stop();
  private:
    byte inverter1, inverter2, enable;
	bool inverse;
};
#endif
