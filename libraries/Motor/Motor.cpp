#include "Motor.h"
/*
   @brief costruttore dell'oggetto motore
*/
Motor::Motor(byte e, byte i1, byte i2) {
  inverter1 = i1;
  inverter2 = i2;
  enable = e;
  pinMode(inverter1, OUTPUT);
  digitalWrite(inverter1, LOW);
  pinMode(inverter2, OUTPUT);
  digitalWrite(inverter2, HIGH);
  pinMode(enable, OUTPUT);
  analogWrite(enable, 0);
}

/*
   @brief metodo che muove di un 'passo' una coppia di motori
*/
void Motor::start(byte speed, bool inverse) {
	this->inverse=inverse;
    analogWrite(enable, speed);
    digitalWrite(inverter1, !inverse);
    digitalWrite(inverter2, inverse);
}

void Motor::setSpeed(byte speed) {
	start(speed, inverse);
}

void Motor::stop() {
  digitalWrite(enable, LOW);
}
