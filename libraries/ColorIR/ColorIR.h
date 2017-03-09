#ifndef ColorIR_h
#define ColorIR_h

#include "Arduino.h"

#define L_CIR 14
#define R_CIR 15

#define BLACK 550
#define MIRROR 250

class ColorIR {
  public:
    int read();
};
#endif
