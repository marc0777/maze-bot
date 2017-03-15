#include "Moviment.h"

Moviment::Moviment (short speed, short rightK, short leftK) {
  motorL = new Motor(L_EN, L_IN1, L_IN2);
  motorR = new Motor(R_EN, R_IN1, R_IN2);
  this->speed = speed;
  kR = rightK;
  kL = leftK;
}

void Moviment::go(bool invert) {
  motorR->start(speed + kR, invert);
  motorL->start(speed + kL, invert);
}

void Moviment::rotate(bool invert) {
  motorR->start(205 , !invert);
  motorL->start(205 , invert);
}

void Moviment::rotate(bool invert,short s) {
  motorR->start(s, !invert);
  motorL->start(s , invert);
}

void Moviment::setSpeed(int s){
  speed=s;
}
void Moviment::setOffset(short rightK,short leftK){
  kR = rightK;
  kL = leftK;
}
int Moviment::getSpeed(){
  return speed;
} 
void Moviment::stop() {
  motorR->stop();
  motorL->stop();
}


