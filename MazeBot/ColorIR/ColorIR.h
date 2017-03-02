#ifndef ColorIR_h
#define ColorIR_h

#include <Arduino.h>

#define BLACK 550
#define MIRROR 250

#define R_CIR 14
#define L_CIR 15

class ColorIR{
  public:
    ColorIR();
    int surfaceType(); 
};
#endif

