#include "Color.h"

Color::Color(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

bool Color::read(){
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  int R = pulseIn(sensorOut, LOW);
  return R < 100;
}
