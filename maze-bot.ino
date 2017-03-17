#include <Arduino.h>
#include <ColorIR.h>
#include <DistanceIR.h>
#include <Matrix.h>
#include <Temperature.h>
#include <DistanceUS.h>
#include <Motion.h>

Motion mov;
Matrix mat; // Matrice che rappresenta il maze
ColorIR color; // Sensore di colore
// Sensori di distanza
DistanceIR infrared [8] = {DistanceIR(A0, 25, 93), DistanceIR(A1, 25, 93), DistanceIR(A2, 25, 93), DistanceIR(A3, 25, 93), DistanceIR(A4, 25, 93), DistanceIR(A5, 25, 93), DistanceIR(A6, 25, 93), DistanceIR(A7, 25, 93)};
// usltrasonic[n] : n = : 0 = destra, 1 = dietro, 2 = sinistra, 3 = avanti
DistanceUS ultrasonic [4] = {DistanceUS(44, 45, 5, 93), DistanceUS(46, 47, 5, 93), DistanceUS(48, 49, 5, 93), DistanceUS(50, 51, 5, 93)};

Temperature temps [2] = {Temperature(0x5A), Temperature(0x5C)}; // Sensori temperatura

void drive(){  /// Funzione che guida tutto
  float dist = ultrasonic[3].read() - 30;
  mov.go();
  bool black = false;
  while (ultrasonic[3].read() > dist){
    /* Controllo del nero
    se è nero torna indietro e gira
    se è nero black = true;
    */
  }
  if (!black) {
    mov.stop();
  }
}

void setup(){
  Serial.begin(9600);
  Serial.println("Avvio!");
}

void loop(){
  drive();
}
