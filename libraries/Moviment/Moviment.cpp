#include "Moviment.h"

Moviment::Moviment (byte velocity, byte rightK, byte leftK) {
  speed = velocity;
  kR = rightK;
  kL = leftK;
}

void Moviment::go() {
  go(false);
}

void Moviment::go(bool invert) {
  motorFR.start(bound(speed + kR, 255), !invert);
  motorFL.start(bound(speed + kL, 255), !invert);
  motorRR.start(bound(speed + kR, 255), !invert);
  motorRL.start(bound(speed + kL, 255), !invert);
}

void Moviment::rotate() {
  rotate(false);
}

void Moviment::rotate(bool invert) {
  motorFR.start(bound((speed + kR) , 255), !invert);
  motorFL.start(bound((speed + kL) , 255), invert);
  motorRR.start(bound((speed + kR) , 255), !invert);
  motorRL.start(bound((speed + kL) , 255), invert);
}

void Moviment::stop() {
  motorFR.stop();
  motorFL.stop();
  motorRR.stop();
  motorRL.stop();
}

void Moviment::setSpeed(byte velocity) {
  speed = velocity;
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
