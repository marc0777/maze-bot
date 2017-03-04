
#ifndef _Ultrasonic_H_
#define _Ultrasonic_H_

#include <stddef.h>
#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <Wprogram.h>
#endif

class Ultrasonic
{
	public:
		Ultrasonic(int ep,int tp);
		float read();
    //float get();
		float v = 0;
	private:
		int _trigPin;
		int _EchoPin;
		float _cmDivisor;
		
};
#endif
