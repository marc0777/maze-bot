#include "Moviment.h"

Moviment::Moviment (int speed, int rightK, int leftK) {

  dist[0] = new DistanceIR(A0, 25, 93, 1080);
  dist[1] = new DistanceIR(A1, 25, 93, 1080);
  dist[2] = new DistanceIR(A2, 25, 93, 1080);//destra1
  dist[3] = new DistanceIR(A3, 25, 93, 1080);//destra2
  dist[4] = new DistanceIR(A4, 25, 93, 1080);//dietro1
  dist[5] = new DistanceIR(A5, 25, 93, 1080);//dietro2
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
  for(int i=0; i<N_SEN;i++){
    distanceRead[i]=dist[i]->distance();
  }
  if(((distanceRead[2]-distanceRead[3])>0.5)||((distanceRead[3]-distanceRead[2])>0.5)||(distanceRead[2]<15)){
    rotate(true);
    while(dist[4]->distance()>30&&dist[5]->distance()>30);
    while(dist[4]->distance()>dist[5]->distance()+0.1&&dist[4]->distance()<dist[5]->distance()-0.1);
    stop();
    if(dist[4]->distance()<12.5){
      go(true);
      while(((dist[4]->distance()<12.6&&dist[4]->distance())>(12.4&&dist[4]->distance())<(12.6&&dist[4]->distance()>12.4)));
      stop();
    }
    else if(dist[4]->distance()>12.5){
      go(false);
      while(((dist[4]->distance()<12.6&&dist[4]->distance())>(12.4&&dist[4]->distance())<(12.6&&dist[4]->distance()>12.4)));
      stop();
    }
    rotate(false);
    while(dist[2]->distance()>30&&dist[3]->distance()>30);
    while((dist[2]->distance()>dist[3]->distance()+0.1)&&(dist[2]->distance()<dist[3]->distance()-0.1));
    stop();
  }
}

