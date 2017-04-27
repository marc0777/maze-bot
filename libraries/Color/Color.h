#ifndef Color_h
#define Color_h

#include <Arduino.h>

#define S0 8
#define S1 7
#define S2 6
#define S3 5
#define sensorOut 4

class Color{ //http://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
public:
  Color();
  bool read(); /// 0 = nero 1 = bianco
};
#endif
