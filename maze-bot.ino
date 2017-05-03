#include <Color.h>
#include <Matrix.h>
#include <Temperature.h>
#include <DistanceUS.h>
#include <Motion.h>

#define ADCTOV 0.0149589739 //costante per il calcolo della tensione della batteria dai pin analogici
#define INTERRUPT 2
#define DEBUG TRUE
#define US_FRONTR 0
#define US_FRONTL 1
#define US_RIGHT 2
#define US_LEFT 3
#define RAMP 20

int inclination;
bool turning = false;

Motion mov(&turning); // tutti i mov.back() sono stati sostituiti da mov.go(true);
Matrix mat; // Matrice che rappresenta il maze
Color *color; // Sensore di colore
Temperature temps[2] = {Temperature(0x5B), Temperature(0x5A)}; // Sensori temperatura 5B sinistra, 5A destra
DistanceUS ultrasonic[4] = {DistanceUS(40, 42), DistanceUS(36, 38), DistanceUS(32, 34),
                            DistanceUS(28, 30)
                           };

void receiveEvent(int howMany) {
  byte data = Wire.read();
  if (data == 255) turning = false;
  else inclination = data - 90;
}

float batStats() {
  return analogRead(A0) * ADCTOV;
}

//TODO accendere led RGB
void victim() {
#ifdef DEBUG
  Serial.println("Corpo rilevato");
#endif
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

#ifdef DEBUG
    Serial.println("Robot raddrizzato");
#endif
  }
#ifdef DEBUG
  else Serial.println("Robot già dritto");
#endif
}

void drive() {  /// Funzione che guida tutto
  if (mat.keep) {
    mat.check(temps[1].readObj() - temps[1].readAmb(), temps[0].readObj() - temps[0].readAmb(), ultrasonic[US_RIGHT].read(), ultrasonic[US_LEFT].read(), color->read());
#ifdef DEBUG
    Serial.println("Controllo cella: " +  mat.isVisited() ? "cella visitata" : "");
#endif
    if (mat.isHot()) victim();
    switch (mat.getDir(ultrasonic[US_RIGHT].read(), ultrasonic[US_FRONTR].read(), ultrasonic[US_LEFT].read())) {
      case 1 :
#ifdef DEBUG
        Serial.print("Giro a destra ");
#endif
        mat.rotate(false);
        mov.rotate();
        break;
      case 3 :
#ifdef DEBUG
        Serial.print("Giro a sinistra ");
#endif
        mat.rotate(true);
        mov.rotate(true);
        break;
      case 4 :
#ifdef DEBUG
        Serial.print("Mi giro di 180° ");
#endif
        for (int i = 0; i < 2; i++) {
          mat.rotate(false);
          mov.rotate();
        }
        break;
    }
    mov.stop();
    float dist = ultrasonic[US_FRONTR].read() - 30;
    mat.go();
    mov.go();
#ifdef DEBUG
    Serial.println(" e vado avanti");
#endif
    bool black = false;
    while (ultrasonic[US_FRONTR].read() > dist && !black) {
      Serial.print(dist);
      Serial.print("\t");
      Serial.println(ultrasonic[US_FRONTR].read());
      if (color->read() == 2) {
#ifdef DEBUG
        Serial.print("Trovata cella nera ");
#endif
        mov.stop();
        mat.check(0.0, 0.0, 0.0, 0.0, 2); //Controllo se sono in una casella proibita
        mat.back();
        dist += 30;
        mov.go(true);
        while (ultrasonic[US_FRONTR].read() <= dist);
#ifdef DEBUG
        Serial.println("quindi torno indietro");
#endif
        black = true;
      }
      // Se rileva salita
      mov.inclination();
      if (inclination >= RAMP || inclination <= -RAMP) {
#ifdef DEBUG
        Serial.print("Rampa trovata");
#endif
        mat.back();
        mat.changeFloor();
        while (inclination >= RAMP || inclination <= -RAMP) {
          mov.inclination();
          delay(50);
        }
        dist = ultrasonic[US_FRONTR].read() - 5;
#ifdef DEBUG
        Serial.println(" e completata");
#endif
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
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Avvio!");
  Serial.print("Tensione batteria: ");
  Serial.print(batStats());
  Serial.println("V");
#endif
  color = new Color();
  pinMode(INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT), pause, FALLING);
  //straightens();
}

void loop() {
  //  drive();
  mov.go();
}
