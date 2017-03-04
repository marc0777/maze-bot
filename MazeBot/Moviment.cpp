#include "Moviment.h"

Moviment::Moviment (int speed, int rightK, int leftK) {

  dist[0] = new DistanceIR(A0, 25, 93, 1080);
  dist[1] = new DistanceIR(A1, 25, 93, 1080);
  dist[2] = new DistanceIR(A2, 25, 93, 1080);
  dist[3] = new DistanceIR(A3, 25, 93, 1080);
  dist[4] = new DistanceIR(A4, 25, 93, 1080);
  dist[5] = new DistanceIR(A5, 25, 93, 1080);
  dist[6] = new DistanceIR(A6, 25, 93, 1080);
  dist[7] = new DistanceIR(A7, 25, 93, 1080);
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
  motorR->start((speed + kR) * 2, !invert);
  motorL->start((speed + kL) * 2, invert);
}

void Moviment::stop() {
  motorR->stop();
  motorL->stop();
}

void Moviment::raddrizzati() {
  for (int i = 0; i < N_SEN; i++) {
    distanceRead[i] = dist[i]->distance();
    for (int j = 0; i < N_SEN; i++) {
      if (controllo(dist[i], dist[++i])) {
        
      }
    }
  }
}

bool Moviment::controllo(int d1,int d2) {
  return (d1==d2)&&(d1 > 20);
}

