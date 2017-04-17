#include <Arduino.h>
#include <ColorIR.h>
#include <Matrix.h>
#include <Temperature.h>
#include <DistanceUS.h>
#include <Motion.h>

#define INTERRUPT 2
#define DEBUG TRUE
#define ROTATEDELAY 1000
#define US_AVANTI 0
#define US_DESTRA 1
#define US_DIETRO 2
#define US_SINISTRA 3

#define inclination 0
//TODO aggiungere una funzione che ritorni l'inclinazione

Motion mov;
Matrix mat; // Matrice che rappresenta il maze
ColorIR color; // Sensore di colore
// usltrasonic[n] : n = : 0 = destra, 1 = dietro, 2 = sinistra, 3 = avanti
DistanceUS ultrasonic[4] = {DistanceUS(44, 45, 5, 93), DistanceUS(46, 47, 5, 93), DistanceUS(48, 49, 5, 93),
  DistanceUS(50, 51, 5, 93)
};

Temperature temps[2] = {Temperature(0x5A), Temperature(0x5C)}; // Sensori temperatura 5A sinistra, 5C destra

bool isStraight(){
  return (abs(ultrasonic[US_AVANTI].read()-ultrasonic[US_DIETRO].read()))<1;
}

void straightens(){
  if(!dritto()){
    mov.rotate(true,true);
    while(!dritto());
    mov.stop();
  }
}

void drive() {  /// Funzione che guida tutto
  if(mat.keep) {
    mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[0].read(), ultrasonic[2].read(), inclination, color.read());
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
    while (ultrasonic[3].read() > dist) {
      if (color.read() == 2) {
        mov.stop();
        //mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[0].read(), ultrasonic[2].read(), color.read());
        mat.check(0, 0, 0, 0, 0, color.read());
        mat.back();
        //TODO andare indietro fino al centro della casella
      }
    }
    mov.stop();
  }
}

void pause () {
  byte state = mov.get();
  while (digitalRead(INTERRUPT));
  mov.set(state);
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
