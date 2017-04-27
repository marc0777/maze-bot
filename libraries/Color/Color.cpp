#include "Color.h"

Color::Color(){
  mirror = readIR();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

byte Color::read(){ //@return 0 se sotto non c'è niente, 1 se c'è uno specchio e 2 se è nero.
  byte color;
  if(readIR() > mirror - MERROR && readIR() < mirror + MERROR) color = 1;
  else {
    // Setting red filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Reading the output frequency
    int R = pulseIn(sensorOut, LOW);
    color =  R < 100? 0 : 2;
  }
  return color;
}

unsigned short Color::readIR() {
  unsigned short media = analogRead(A0);
  delay(100);
  media += analogRead(A1);
  return media >> 1;
}
