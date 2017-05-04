#include "Moviment.h"

Moviment::Moviment (byte velocity) {
  speed = velocity;
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

void Moviment::setK(int rightK, int leftK) {
  kR = rightK;
  kL = leftK;
}

short Moviment::bound(short n, short max) {
  return (n > max) ? max : n;
}
