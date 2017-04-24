#include <Arduino.h>
#include <ColorIR.h>
#include <Matrix.h>
#include <Temperature.h>
#include <DistanceUS.h>
#include <Motion.h>

#define ADCTOV 0.0149589739 //costante per il calcolo della tensione della batteria dai pin analogici
#define INTERRUPT 2
#define DEBUG TRUE
#define ROTATEDELAY 1000
#define US_AVANTI 0
#define US_DESTRA 1
#define US_DIETRO 2
#define US_SINISTRA 3

#define inclination 0
//TODO aggiungere una funzione che ritorni l'inclinazione

Motion mov; // tutti i mov.back() sono stati sostituiti da mov.go(true);
Matrix mat; // Matrice che rappresenta il maze
ColorIR color; // Sensore di colore
// usltrasonic[n] : n = : 0 = destra, 1 = dietro, 2 = sinistra, 3 = avanti
DistanceUS ultrasonic[4] = {DistanceUS(44, 45, 5, 93), DistanceUS(46, 47, 5, 93), DistanceUS(48, 49, 5, 93),
                            DistanceUS(50, 51, 5, 93)
                           };

Temperature temps[2] = {Temperature(0x5A), Temperature(0x5C)}; // Sensori temperatura 5A sinistra, 5C destra

bool isStraight() {
  return (abs(ultrasonic[US_AVANTI].read() - ultrasonic[US_DIETRO].read())) < 1;
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
    mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[0].read(), ultrasonic[2].read(), color.read());
    if (mat.isHot()) {
      //TODO accendere led RGB
      digitalWrite(13, 1);
      delay(1000);
      digitalWrite(13, 0);
      delay(500);
      digitalWrite(13, 1);
      delay(800);
      digitalWrite(13, 0);
    }
    switch (mat.getDir(ultrasonic[0].read(), ultrasonic[3].read(), ultrasonic[2].read())) {
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
    float dist = ultrasonic[3].read() - 30;
    mat.go();
    mov.go();
    bool black = false;
    while (ultrasonic[3].read() > dist && !black) {
      if (color.read() == 2) {
        mov.stop();
        mat.check(0.0, 0.0, 0.0, 0.0, color.read()); //Controllo se sono in una casella proibita
        mat.back();
        dist += 30;
        mov.go(true);
        while (ultrasonic[US_AVANTI].read() < dist);
        black = true;
      }
      // Se rileva salita
      if (inclination >= 10 || inclination <= -10) {
        mat.back();
        mat.changeFloor();
        while (inclination >= 10 || inclination <= -10);
        dist = ultrasonic[3].read() - 5;
      }
    }
    mov.stop();
  }
}

void pause () {
  while (digitalRead(INTERRUPT));
  mat.reset();
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Avvio!");
#endif
  pinMode(INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT), pause, FALLING);
  for (int i = 0; i < 2; i++) temps[i].begin();
  straightens();
}

void loop() {
  drive();
}
