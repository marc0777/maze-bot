#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
class Motor
{
	public:
		Motor(int e,int i1,int i2);
		void start(int power, bool inverse);
		void stop();
		
	private:
    short inverter1,inverter2, enable;
};
#endif
