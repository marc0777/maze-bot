#include "Moviment.h"

// defining constant pin for motors
#define R_EN 4
#define R_IN1 3
#define R_IN2 2
#define L_EN 7
#define L_IN1 5
#define L_IN2 6

Moviment::Moviment (int speed, int rightK, int leftK) {
  this->speed = speed;
  kR = rightK;
  kL = leftK;
  motorR = new Motor(R_EN,R_IN1,R_IN2);
  motorL = new Motor(L_EN,L_IN1,L_IN2);
}

void Moviment::go(bool invert) {
  motorR->start(speed+kR, invert);
  motorL->start(speed+kL, invert);
}

void Moviment::rotate(bool invert) {
  motorR->start(speed+kR, !invert);
  motorL->start(speed+kL, invert);
}

void Moviment::stop() {
  motorR->stop();
  motorL->stop();
}

