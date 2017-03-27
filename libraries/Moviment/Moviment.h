#ifndef Moviment_h
#define Moviment_h

#include "Motor.h"

#define FR_EN 3
#define FR_IN1 4
#define FR_IN2 5
#define FL_EN 6
#define FL_IN1 7
#define FL_IN2 8
#define RR_EN 9
#define RR_IN1 10
#define RR_IN2 11
#define RL_EN 12
#define RL_IN1 13
#define RL_IN2 14

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
  private:
    short bound (short n, short max);
    Motor motorFR = Motor(FL_EN, FL_IN1, FL_IN2);
    Motor motorFL = Motor(FR_EN, FR_IN1, FR_IN2);
    Motor motorRR = Motor(RL_EN, RL_IN1, RL_IN2);
    Motor motorRL = Motor(RR_EN, RR_IN1, RR_IN2);
    byte speed;
    byte kR;
    byte kL;
};
#endif
