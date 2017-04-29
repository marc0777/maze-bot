#include <Arduino.h>
#include <Color.h>
#include <Matrix.h>
#include <Temperature.h>
#include <DistanceUS.h>
#include <Motion.h>

#define ADCTOV 0.0149589739 //costante per il calcolo della tensione della batteria dai pin analogici
#define INTERRUPT 2
#define DEBUG TRUE
#define ROTATEDELAY 1000
#define US_FRONTR 0
#define US_FRONTL 1
#define US_RIGHT 2
#define US_LEFT 3
#define RAMP 20

#define inclination 0
//TODO aggiungere una funzione che ritorni l'inclinazione

Motion mov; // tutti i mov.back() sono stati sostituiti da mov.go(true);
Matrix mat; // Matrice che rappresenta il maze
Color *color; // Sensore di colore
DistanceUS ultrasonic[4] = {DistanceUS(40, 42, 5, 93), DistanceUS(36, 38, 5, 93), DistanceUS(32, 34, 5, 93),
                            DistanceUS(28, 30, 5, 93)
                           };

Temperature temps[2] = {Temperature(0x5B), Temperature(0x5A)}; // Sensori temperatura 5B sinistra, 5A destra

float batStats() {
  return analogRead(A0) * ADCTOV;
}

//TODO accendere led RGB
void victim() {
    digitalWrite(13, 1);
    delay(1000);
    digitalWrite(13, 0);
    delay(500);
    digitalWrite(13, 1);
    delay(800);
    digitalWrite(13, 0);
}

bool isStraight() {
  return (abs(ultrasonic[US_FRONTR].read() - ultrasonic[US_FRONTL].read())) < 1;
}

void straightens() {
  if (!isStraight()) {
    mov.rotate(true, true);
    while (!isStraight());
    mov.stop();
  }
}

void drive() {  /// Funzione che guida tutto
  if (mat.keep) {
    mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[US_RIGHT].read(), ultrasonic[US_LEFT].read(), color->read());
    if (mat.isHot()) victim();
    switch (mat.getDir(ultrasonic[US_RIGHT].read(), ultrasonic[US_FRONTR].read(), ultrasonic[US_LEFT].read())) {
      case 1 :
        mat.rotate(false);
        mov.rotate();
        break;
      case 3 :
        mat.rotate(true);
        mov.rotate(true);
        break;
      case 4 :
        for (int i = 0; i < 2; i++) {
          mat.rotate(false);
          mov.rotate();
        }
        break;
    }
    delay(ROTATEDELAY);
    float dist = ultrasonic[US_FRONTR].read() - 30;
    mat.go();
    mov.go();
    bool black = false;
    while (ultrasonic[US_FRONTR].read() > dist && !black) {
      if (color->read() == 2) {
        mov.stop();
        mat.check(0.0, 0.0, 0.0, 0.0, 2); //Controllo se sono in una casella proibita
        mat.back();
        dist += 30;
        mov.go(true);
        while (ultrasonic[US_FRONTR].read() <= dist);
        black = true;
      }
      // Se rileva salita
      if (inclination >= RAMP || inclination <= -RAMP) {
        mat.back();
        mat.changeFloor();
        while (inclination >= RAMP || inclination <= -RAMP);
        dist = ultrasonic[US_FRONTR].read() - 5;
      }
    }
    mov.stop();
  }
}

void pause () {
  detachInterrupt(digitalPinToInterrupt(INTERRUPT));
  while (digitalRead(INTERRUPT));
  mat.reset();
  attachInterrupt(digitalPinToInterrupt(INTERRUPT), pause, FALLING);
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Avvio!");
#endif
  color = new Color();
  pinMode(INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT), pause, FALLING);
  for (int i = 0; i < 2; i++) temps[i].begin();
  straightens();
}

void loop() {
  drive();
}
