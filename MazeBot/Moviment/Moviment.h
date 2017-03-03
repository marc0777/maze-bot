#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <Arduino.h>
#include "Motor.h"

// defining constant pin for motors
#define R_EN 4
#define R_IN1 2
#define R_IN2 3
#define L_EN 7
#define L_IN1 6
#define L_IN2 5

#include <Arduino.h>

class Moviment {
  public:
    Moviment (int speed, int rightK, int leftK); 
    void go (bool invert);
    void rotate (bool invert);
    void stop();
  private:
    Motor *motorR;
    Motor *motorL;
  
    short speed;
    short kR;
    short kL;
};
#endif
