#include "Moviment.h"

Moviment::Moviment (byte speed, byte rightK, byte leftK) {
  motorL = new Motor(L_EN, L_IN1, L_IN2);
  motorR = new Motor(R_EN, R_IN1, R_IN2);
  this->speed = speed;
  kR = rightK;
  kL = leftK;
}

void Moviment::go() {
  go(false);
}

void Moviment::go(bool invert) {
  motorR->start(bound(speed + kR, 255), !invert);
  motorL->start(bound(speed + kL, 255), !invert);
}

void Moviment::rotate() {
  rotate(false);
}

void Moviment::rotate(bool invert) {
  motorR->start(bound((speed + kR) , 255), !invert);
  motorL->start(bound((speed + kL) , 255), invert);
}

void Moviment::stop() {
  motorR->stop();
  motorL->stop();
}

void Moviment::setSpeed(byte speed) {
  this->speed = speed;
}

void Moviment::setK(byte rightK, byte leftK) {
  kR = rightK;
  kL = leftK;
}

void Moviment::set(byte state) {
  switch (state) {
    case 0:
      stop();
      break;
    case 1:
      go(false);
      break;
    case 2:
      rotate(false);
      break;
    case 3:
      go(true);
      break;
    case 4:
      rotate(true);
      break;
  }
}

byte Moviment::get() {
  return state;
}

short Moviment::bound(short n, short max) {
  return (n > max) ? max : n;
}
