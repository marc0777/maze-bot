#ifndef Color_h
#define Color_h

#include <Arduino.h>

#define S0 8
#define S1 7
#define S2 6
#define S3 5
#define sensorOut 4
#define MERROR 100 // Error for mirror recognition


class Color {
public:
  Color();
  byte read();
private:
  unsigned short readIR();
  unsigned short mirror;
};
#endif
