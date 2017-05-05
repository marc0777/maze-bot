#include "Moviment.h"

Moviment::Moviment (byte velocity) {
  state=0;
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
  motorFR.setSpeed(velocity);
  motorFL.setSpeed(velocity);
  motorRR.setSpeed(velocity);
  motorRL.setSpeed(velocity);
}

void Moviment::setK(int rightK, int leftK) {
  kR = rightK;
  kL = leftK;
  motorFR.setSpeed(bound((speed + kR) , 255));
  motorFL.setSpeed(bound((speed + kL) , 255));
  motorRR.setSpeed(bound((speed + kR) , 255));
  motorRL.setSpeed(bound((speed + kL) , 255));
}

short Moviment::bound(short n, short max) {
  return (n > max) ? max : n;
}
