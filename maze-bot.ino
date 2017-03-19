#include <Arduino.h>
#include <ColorIR.h>
#include <DistanceIR.h>
#include <Matrix.h>
#include <Temperature.h>
#include <DistanceUS.h>
#include <Motion.h>

#define DEBUG TRUE

Motion mov;
Matrix mat; // Matrice che rappresenta il maze
ColorIR color; // Sensore di colore
// Sensori di distanza
DistanceIR infrared[8] = {DistanceIR(A0, 25, 93), DistanceIR(A1, 25, 93), DistanceIR(A2, 25, 93),
                          DistanceIR(A3, 25, 93), DistanceIR(A4, 25, 93), DistanceIR(A5, 25, 93),
                          DistanceIR(A6, 25, 93), DistanceIR(A7, 25, 93)};
// usltrasonic[n] : n = : 0 = destra, 1 = dietro, 2 = sinistra, 3 = avanti
DistanceUS ultrasonic[4] = {DistanceUS(44, 45, 5, 93), DistanceUS(46, 47, 5, 93), DistanceUS(48, 49, 5, 93),
                            DistanceUS(50, 51, 5, 93)};

Temperature temps[2] = {Temperature(0x5A), Temperature(0x5C)}; // Sensori temperatura 5A sinistra, 5C destra

void drive() {  /// Funzione che guida tutto
    mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[0].read(), ultrasonic[2].read(), color.read());
    /*if(ultrasonic[0].read() >= DISTWALL){
      mat.rotate(false);
      mov.rotate();
    }else if(ultrasonic[]) */
    float dist = ultrasonic[3].read() - 30;
    mat.go();
    mov.go();
    while (ultrasonic[3].read() > dist) {
        if (color.read() == 2) {
          mov.stop();
          mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[0].read(), ultrasonic[2].read(), color.read());
          mat.back();
          //TODO andare indietro fino al centro della casella
        }
    }
    mov.stop();
}

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Avvio!");
  #endif
}

void loop() {
    drive();
}
