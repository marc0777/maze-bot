#include "Arduino.h"
#include "ColorIR.h"
#include "DistanceIR.h"
#include "Moviment.h"
#include "MLX90614.h"
#include "Ultrasonic.h"

Moviment mov(120, 0, -30);
Ultrasonic US0(44, 45); //destra
Ultrasonic US1(46, 47); //dietro
Ultrasonic US2(48, 49); //sinistra
Ultrasonic US3(50, 51); //avanti
Ultrasonic US[4] = {US0, US1, US2, US3};
MLX90614 tDestra = MLX90614(0x5A);
MLX90614 tSinistra = MLX90614(0x5C);
ColorIR colore = ColorIR();
 
double tempAmb;
double tempDestra;
double tempSinistra;

short direction = 0;
short start[2] {0, 0};

// 36,38,40,42  8,9,10 per RGB

void vittima(bool dir){
  mov.rotate(dir);
  delay(500);
  mov.stop();
  mov.go(true);
  while(US[3].read()>10);
  mov.stop();
  
  digitalWrite(36, HIGH);
  digitalWrite(38, HIGH);
  digitalWrite(40, HIGH);
  digitalWrite(42, HIGH);
  analogWrite(10,255);
  delay(1000);
  digitalWrite(36, LOW);
  digitalWrite(38, LOW);
  digitalWrite(40, LOW);
  digitalWrite(42, LOW);
  analogWrite(10,0);

}

void sempreADestra() {
  /*for(int i=0;i<4;i++){
    Serial.println(US[i].read());
  }*/
  if (US[0].read() > 30) {
    mov.rotate(false);//false=destra
    delay(500);
    mov.stop();
  }
  //    while(x!=90) {
  //      mov.rotate(true);
  //      direction=(direction+1)%4;
  //    }//destro
  else if (US[3].read() < 15)  {
    mov.rotate(true);
    delay(500);
    mov.stop();
  }
  //    while() {//
  //      mov.rotate(false);
  //      direction=(direction-1)%4;
  //    }//sinistro
  if(US[3].read() > 30){
    float fine = US[3].read() - 30;
    mov.go(true);
    while (US[3].read() > fine){
      tempAmb = (tDestra.readAmb()+tSinistra.readAmb())/2; //controllo a destra e sinistra del calore,se trovato si deve girare in quella direzione e sbattersi fortemente sul muro.
      tempDestra = tDestra.readObj();
      tempSinistra = tSinistra.readObj();
      if(tempSinistra-tempAmb>20) uccidiBertoldi(true);
      if(tempDestra-tempAmb>20) uccidiBertoldi(false);
      Serial.print("Destra : ");
      Serial.println(tempDestra-tempAmb);
      Serial.print("Sinistra : ");
      Serial.println(tempSinistra-tempAmb);
    }
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
    //if(colore.surfaceType()!=2)mov.raddrizzati();
  }
}

void setup() { 
  Serial.begin(115200);
  tSinistra.begin();
  tDestra.begin();
}



void loop() {
  Serial.println();
  primoVito();
  
}
