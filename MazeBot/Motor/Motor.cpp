#include <stdio.h>
#include <stdlib.h>
#include "Motor.h"
/*
 * @brief costruttore dell'oggetto motore
 */
Motor::Motor(int i1,int i2,int e){
  inverter1=i1;
  inverter2=i2;
  enable=e;
  pinMode(inverter1,OUTPUT);
  digitalWrite(inverter1,LOW);
  pinMode(inverter2,OUTPUT);
  digitalWrite(inverter2,HIGH);
	pinMode(enable,OUTPUT);
	analogWrite(enable,0);
}



/*
 * @brief metodo che muove di un 'passo' una coppia di motori
 */
void Motor::startMotor(int power){
    if(power>= 0){
      analogWrite(enable, power);
      digitalWrite(inverter1,LOW);
      digitalWrite(inverter2,HIGH);
    }
    else{
      analogWrite(enable, -power);
      digitalWrite(inverter1,HIGH);
      digitalWrite(inverter2,LOW);
    }
}
