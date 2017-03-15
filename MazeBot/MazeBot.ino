#include "Arduino.h"
#include "ColorIR.h"
#include "DistanceIR.h"
#include "Moviment.h"
#include "MLX90614.h"
#include "Ultrasonic.h"
#include "IMU.h"

Moviment mov(120, 0, -30);
Ultrasonic US0(44, 45); //destra
Ultrasonic US1(46, 47); //dietro
Ultrasonic US2(48, 49); //sinistra
Ultrasonic US3(50, 51); //avanti
Ultrasonic US[4] = {US0, US1, US2, US3};

DistanceIR dist6(A0, 25, 93, 1080);//avanti sx
DistanceIR dist7(A1, 25, 93, 1080);//avanti dx
DistanceIR dist0(A2, 25, 93, 1080);//destra a
DistanceIR dist1(A3, 25, 93, 1080);//destra d
DistanceIR dist2(A4, 25, 93, 1080);//dietro dx
DistanceIR dist3(A5, 25, 93, 1080);//dietro sx
DistanceIR dist4(A6, 25, 93, 1080);//sinistra a
DistanceIR dist5(A7, 25, 93, 1080);//sinistra d
DistanceIR dist[8] = {dist0, dist1, dist2, dist3, dist4, dist5, dist6, dist7};

MLX90614 tDestra = MLX90614(0x5A);
MLX90614 tSinistra = MLX90614(0x5C);
ColorIR colore = ColorIR();
IMU imu;

double tempAmb;
double tempDestra;
double tempSinistra;
float endRotation;
short direction = 0;
short usNum;
float k1;
float k2;
int tVittima = 0;
//short start[2] {0, 0};\\\\\\\

// 36,38,40,42  8,9,10 per RGB

float modulo(float n, float m) {
  while (n > m) {
    n -= m;
  }
  return n;
}
void rotate(bool dir) {
  mov.rotate(dir);
  if (dir) {
    endRotation = imu.getYaw() - 50;
    if (endRotation < 0) {
      endRotation += 360;
      while (imu.getYaw() > endRotation) {
        delay(10);
      }
    }
    else while (imu.getYaw() > endRotation) {
        delay(10);
      }

  }//sinistra
  else {
    endRotation = imu.getYaw() + 50;
    if (endRotation > 360) {
      endRotation -= 360;
      while (imu.getYaw() <= 355);
      delay(20);
      while (imu.getYaw() < endRotation) ;
    }
    else {
      while (imu.getYaw() < endRotation) ;
    }
  }//destra
  mov.stop();
}

void uccidiBertoldi(bool dir) {
  if (dir) {
    if (US[2].read() > 20) {
      rotate(dir);
      mov.stop();
      mov.go(true);
      while (US[3].read() < 10);
      mov.stop();
      digitalWrite(36, HIGH);
      digitalWrite(38, HIGH);
      digitalWrite(40, HIGH);
      digitalWrite(42, HIGH);
      analogWrite(8, 255);
      delay(3000);
      digitalWrite(36, LOW);
      digitalWrite(38, LOW);
      digitalWrite(40, LOW);
      digitalWrite(42, LOW);
      analogWrite(8, 00);
      if (dir) {
        mov.go(false);
        while (US[1].read() > 10);
        mov.stop();
      }
    }
    else {
      mov.stop();
      digitalWrite(36, HIGH);
      digitalWrite(38, HIGH);
      digitalWrite(40, HIGH);
      digitalWrite(42, HIGH);
      analogWrite(8, 255);
      delay(3000);
      digitalWrite(36, LOW);
      digitalWrite(38, LOW);
      digitalWrite(40, LOW);
      digitalWrite(42, LOW);
      analogWrite(8, 00);
    }
  }
  else {
    if (US[0].read() > 20) {
      rotate(dir);
      mov.stop();
      mov.go(true);
      while (US[3].read() > 10);
      mov.stop();
      digitalWrite(36, HIGH);
      digitalWrite(38, HIGH);
      digitalWrite(40, HIGH);
      digitalWrite(42, HIGH);
      analogWrite(8, 255);
      delay(3000);
      digitalWrite(36, LOW);
      digitalWrite(38, LOW);
      digitalWrite(40, LOW);
      digitalWrite(42, LOW);
      analogWrite(8, 00);
      if (dir) {
        mov.go(false);
        while (US[1].read() > 10);
        mov.stop();
      }
    }
    else {
      mov.stop();
      digitalWrite(36, HIGH);
      digitalWrite(38, HIGH);
      digitalWrite(40, HIGH);
      digitalWrite(42, HIGH);
      analogWrite(8, 255);
      delay(3000);
      digitalWrite(36, LOW);
      digitalWrite(38, LOW);
      digitalWrite(40, LOW);
      digitalWrite(42, LOW);
      analogWrite(8, 00);
    }

  }
  //  rotate(!dir);
  //  rotate(!dir);
}

void primoVito() {
  if (US[0].read() > 40) {
    //    analogWrite(10, 100);
    rotate(false);
    //mov.rotate(false);
    //    delay(600);
    raddrizzati();
    //  analogWrite(10, 0);
  }
  //    while(x!=90) {
  //      mov.rotate(true);
  //      direction=(direction+1)%4;
  //    }//destro
  else if (US[3].read() < 15 || colore.surfaceType() == 2)  {
    //   analogWrite(8, 150);
    rotate(true);
    raddrizzati();
    //    mov.rotate(true);
    //    delay(600);
    //    analogWrite(8, 0);
  }
  //    while() {//
  //      mov.rotate(false);
  //      direction=(direction-1)%4;
  //    }//sinistro

  float fine = US[3].read() - 30;

  //analogWrite(9, 150);
  if (fine > 5) {
    mov.go(true);

    //    Serial.println(fine);
    while (US[3].read() > fine && US[3].read() > 10 && colore.surfaceType() != 2) {
      Serial.println(mov.getSpeed());
      Serial.println(imu.getPitch());
      if (imu.getPitch() < -10) {
        mov.setSpeed(240);
        mov.setOffset(0, 0);
      }
      else {
        mov.setSpeed(120);
        mov.setOffset(0, -30);
      }
      mov.go(true);

      if (modulo(US[0].read(), 30) > k1) {
        mov.rotate(false);
        delay(2);
      }
      else if (modulo(US[0].read(), 30) < k2) {
        mov.rotate(true);
        delay(2);
      }

      //      float differenza = dist[2].distance() - dist[3].distance();
      //      while (abs(differenza) > 2) {
      //        mov.rotate(differenza < 0,120);
      //        differenza = dist[2].distance() - dist[3].distance();
      //      }
      //      raddrizzati();
      mov.go(true);
      tempAmb = (tDestra.readAmb() + tSinistra.readAmb()) / 2; //controllo a destra e sinistra del calore,se trovato si deve girare in quella direzione e sbattersi fortemente sul muro.
      tempDestra = tDestra.readObj() - tempAmb;
      tempSinistra = tSinistra.readObj() - tempAmb;
      Serial.print(tempAmb);
      Serial.print("\t");
      Serial.print(tempSinistra);
      Serial.print("\t");
      Serial.println(tempDestra);
      if (tempSinistra > 10 && millis() - tVittima > 5000) {
        uccidiBertoldi(true);
        tVittima = millis();
      }
      if (tempDestra > 10 && millis() - tVittima > 5000) {
        uccidiBertoldi(false);
        tVittima = millis();
      }
    }
    if(colore.surfaceType() != 2){mov.go(false);delay(100);}
    if(colore.surfaceType() != 2){mov.go(false);delay(100);}
  }
  else {
    mov.go(true);
    while (US[3].read() > 10 && colore.surfaceType() != 2) {
      //      Serial.println(US[3].read());
      if (modulo(US[0].read(), 30) > k1) {
        mov.rotate(false);
        delay(2);
      }
      else if (modulo(US[0].read(), 30) < k2) {
        mov.rotate(true);
        delay(2);
      }

      //      float differenza = dist[2].distance() - dist[3].distance();
      //      while (abs(differenza) > 2) {
      //        mov.rotate(differenza < 0,120);
      //        differenza = dist[2].distance() - dist[3].distance();
      //      }
      //
      
      raddrizzati();
      mov.go(true);
    }
    if(colore.surfaceType() != 2){mov.go(false);delay(100);}
  }
  raddrizzati();

  //analogWrite(9, 0);
  mov.stop();
}


void raddrizzati() {
//  usNum = 3;
//  for (int i = 0; i < 3; i++) {
//    if (US[i].read() < US[usNum].read())usNum = i;
//  }
//  usNum *= 2;
  float differenza = dist[2].distance() - dist[3].distance();
  while (abs(differenza) > 2) {
    mov.rotate(differenza < 0);
    differenza = dist[2].distance() - dist[3].distance();
  }
  mov.stop();
}

void setup() {
  Serial.begin(9600);
  tSinistra.begin();
  tDestra.begin();
  imu.begin();
  raddrizzati();
  k1 = US[3].read() - 1;
  k2 = k1 + 2;
  //imu.calibrate();
}



void loop() {
  primoVito();
}
