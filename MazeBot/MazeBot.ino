#include "Arduino.h"
#include "ColorIR.h"
#include "DistanceIR.h"
#include "Moviment.h"
#include "Temperature.h"
#include "Ultrasonic.h"

Moviment mov(120, 0, -30);
Ultrasonic US0(44, 45); //destra
Ultrasonic US1(46, 47); //dietro
Ultrasonic US2(48, 49); //sinistra
Ultrasonic US3(50, 51); //avanti
Ultrasonic US[4] = {US0, US1, US2, US3};

short direction = 0;
short start[2] {0, 0};

// 36,38,40,42

void primoVito() {
  digitalWrite(36, HIGH);
  for(int i=0;i<4;i++){
    Serial.println(US[i].read());
  }
  if (US[0].read() > 30) {
    digitalWrite(40, HIGH);
    mov.rotate(false);
    delay(500);
    mov.stop();
    digitalWrite(40,LOW);
  }
  //    while(x!=90) {
  //      mov.rotate(true);
  //      direction=(direction+1)%4;
  //    }//destro
  else if (US[3].read() < 15)  {
    digitalWrite(42, HIGH);
    mov.rotate(true);
    delay(500);
    mov.stop();
    digitalWrite(42,LOW);
  }
  //    while() {//
  //      mov.rotate(false);
  //      direction=(direction-1)%4;
  //    }//sinistro
  if(US[3].read() > 30){
    float fine = US[3].read() - 30;
    mov.go(true);
    while (US[3].read() > fine)int i = 0; //controllo a destra e sinistra del calore,se trovato si deve girare in quella direzione e sbattersi fortemente sul muro.
    mov.stop();
    switch (direction) {
      case 0:
        start[0]++;
        break;
      case 1:
        start[1]++;
        break;
      case 2:
        start[0]--;
        break;
      case 3:
        start[1]--;
        break;
    }
  }
  
    digitalWrite(36,LOW);
}

void setup() { 
  Serial.begin(9600);
}



void loop() {
  primoVito();
}
