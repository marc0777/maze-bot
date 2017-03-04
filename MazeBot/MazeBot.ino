#include "ColorIR/ColorIR.h"
#include "DistanceIR/DistanceIR.h"
#include "Moviment/Moviment.h"
#include "Temperature/Temperature.h"
#include "Ultrasonic/Ultrasonic.h"

Moviment mov(80,0,0);
Ultrasonic US0(44,45);//destra
Ultrasonic US1(46,47);//dietro
Ultrasonic US2(48,49);//sinistra
Ultrasonic US3(50,51);//avanti
Ultrasonic US[4]={US0,US1,US2,US3};

short direction=0;
short start[2]{0,0};


void primoVito(){
  if(US[0].read()>30) {
  mov.rotate(false);
  delay(1500);
  mov.stop();
}
//    while(x!=90) {
//      mov.rotate(true);
//      direction=(direction+1)%4;
//    }//destro
  else if (US[3].read()<30)  {
  mov.rotate(false);
  delay(1500);
  mov.stop();
}
//    while() {//
//      mov.rotate(false);
//      direction=(direction-1)%4;
//    }//sinistro
  float fine = US[3].read()-30;
  mov.go(true);
  while(US[3].read()>fine)int i=0;//controllo a destra e sinistra del calore,se trovato si deve girare in quella direzione e sbattersi fortemente sul muro.
  mov.stop();
  switch(direction){
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

void setup() {}



void loop() {
  
  }
