#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <Arduino.h>
#include "Motor.h"
#include "DistanceIR.h"

// defining constant pin for motors
#define R_EN 4
#define R_IN1 2
#define R_IN2 3
#define L_EN 7
#define L_IN1 6
#define L_IN2 5

#define N_SEN 8


#include <Arduino.h>

class Moviment {
  public:
    Moviment (int speed, int rightK, int leftK); 
    void raddrizzati();
    void go (bool invert);
    void rotate (bool invert);
    void stop();
  private:
    Motor *motorR;
    Motor *motorL;
    bool controllo(int d1,int d2);
    
    DistanceIR *dist[];
    
    short speed;
    short kR;
    short kL;
    int distanceRead[N_SEN];
};
#endif
