
#include <stdio.h>
#include <stdlib.h>
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int ep,int tp)
{
	pinMode(tp,OUTPUT);
	pinMode(ep,INPUT);
	_trigPin = tp;
	_EchoPin = ep;
  _cmDivisor = 58.0;
}

float Ultrasonic::read()
{
	digitalWrite(_trigPin,LOW);
	delayMicroseconds(2);
	digitalWrite(_trigPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigPin,LOW);
  v=pulseIn(_EchoPin,HIGH)/ _cmDivisor;
	return v;
}

