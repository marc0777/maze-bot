#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
  public:
    Motor(byte e, byte i1, byte i2);
    void start(byte speed, bool inverse);
    void setSpeed(byte speed);
    void stop();
  private:
    byte inverter1, inverter2, enable;
	bool inverse;
};

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

#endif
