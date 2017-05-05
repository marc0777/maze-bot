#ifndef Moviment_h
#define Moviment_h

#include "Motor.h"

#define FR_EN 10
#define FR_IN1 8
#define FR_IN2 11
#define FL_EN 5
#define FL_IN1 2
#define FL_IN2 3
#define RR_EN 9
#define RR_IN1 12
#define RR_IN2 13
#define RL_EN 6
#define RL_IN1 7
#define RL_IN2 4

class Moviment {
  public:
    Moviment (byte speed);
    void go();
    void go (bool invert);
    void rotate();
    void rotate (bool invert);
    void stop();
    void setSpeed(byte speed);
    void setK(int rightK, int leftK);
  private:
    short bound (short n, short max);
    Motor motorFR = Motor(FL_EN, FL_IN1, FL_IN2);
    Motor motorFL = Motor(FR_EN, FR_IN1, FR_IN2);
    Motor motorRR = Motor(RL_EN, RL_IN1, RL_IN2);
    Motor motorRL = Motor(RR_EN, RR_IN1, RR_IN2);
	byte state;
    byte speed;
    int kR;
    int kL;
};
#endif
