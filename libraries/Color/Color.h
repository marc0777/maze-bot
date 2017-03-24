#ifndef Color_h
#define Color_h

#include <Arduino.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

class Color{ //http://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
public:
  Color();
  byte read();
private:
};
