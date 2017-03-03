#include "Moviment.h"

Moviment::Moviment (int speed, int rightK, int leftK) {
  this->speed = speed;
  kR = rightK;
  kL = leftK;
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

