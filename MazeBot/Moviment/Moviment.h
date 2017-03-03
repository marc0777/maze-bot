#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <Arduino.h>
#include "Motor.h"


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
