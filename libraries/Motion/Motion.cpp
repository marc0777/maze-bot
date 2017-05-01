#include "Motion.h"

Motion::Motion () {
	Wire.begin();
}

void Motion::stop() {
	set(MOTION_STOP);
}

void Motion::go() {
	set(MOTION_FORWARD);
}

void Motion::go(bool invert) {
	set((invert)?MOTION_BACKWARD:MOTION_FORWARD);
}

void Motion::rotate() {
  set(MOTION_RIGHT);
	wait(0);
}

void Motion::rotate(bool invert) {
	set((invert)?MOTION_LEFT:MOTION_RIGHT);
	wait(0);
}

void Motion::rotate(bool invert, bool infinite) {
	set((infinite)?((invert)?MOTION_LEFT_INFINITE:MOTION_RIGHT_INFINITE):((invert)?MOTION_LEFT:MOTION_RIGHT));
	wait(0);
}

void Motion::set(byte state) {
	Wire.beginTransmission(MOTION_ADDRESS);
	Wire.write(state);
	Wire.endTransmission();
}

byte Motion::get() {
	return request(1,MOTION_ADDRESS);
}

int Motion::inclination() {
	return request(0, MOTION_ADDRESS)-90;
}

byte Motion::request(byte data, byte address) {
  //Scrivo allo slave il dato richiesto
  Wire.beginTransmission(address);
  Wire.write(data+127);
  Wire.endTransmission();
  //Leggo dallo slave il dato di risposta
  Wire.requestFrom(address, 1);
  while (!Wire.available());
  return Wire.read();
}

void Motion::wait(byte until) {
	while(get()!=0) delay (10);
}
