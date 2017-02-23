#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
class Motor
{
	public:
		Motor(int inverter1,int inverter2,int enable);
		void startMotor(int power);
		
		
	private:
    int inverter1,inverter2, enable;
};
#endif
