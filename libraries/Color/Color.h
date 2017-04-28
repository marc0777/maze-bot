#ifndef Color_h
#define Color_h

#include <Arduino.h>

#define S0 52
#define S1 50
#define S2 48
#define S3 46
#define sensorOut 44
#define MERROR 5 // Error for mirror recognition


class Color {
public:
  Color();
  byte read();
private:
  unsigned short readIR();
  unsigned short mirror;
};
#endif
