#ifndef Moviment_h
#define Moviment_h

#include "Motor.h"

#define R_EN 3
#define R_IN1 4
#define R_IN2 5
#define L_EN 6
#define L_IN1 7
#define L_IN2 8

class Moviment {
  public:
    Moviment (byte speed, byte rightK, byte leftK);
    void go();
    void go (bool invert);
    void rotate();
    void rotate (bool invert);
    void stop();
    void setSpeed(byte speed);
    void setK(byte rightK, byte leftK);
    void set(byte state);
    byte get();
  private:
    short bound (short n, short max);
    Motor *motorR;
    Motor *motorL;
    short speed;
    byte kR;
    byte kL;
    byte state;
};
#endif
