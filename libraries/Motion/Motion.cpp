#include "Motion.h"

Motion::Motion (bool *turning) {
	this->turning = turning;
}

void Motion::stop() {
	set(MOTION_STOP);
}

void Motion::go() {
	go(false);
}

void Motion::go(bool invert) {
	set((invert)?MOTION_BACKWARD:MOTION_FORWARD);
}

void Motion::rotate() {
	rotate(false,false);
}

void Motion::rotate(bool invert) {
	rotate(invert,false);
}

void Motion::rotate(bool invert, bool infinite) {
	set((infinite)?((invert)?MOTION_LEFT_INFINITE:MOTION_RIGHT_INFINITE):((invert)?MOTION_LEFT:MOTION_RIGHT));
	*turning=true;
	while(*turning) delay(1);
}

void Motion::set(byte state) {
	Wire.beginTransmission(MOTION_ADDRESS);
	Wire.write(state);
	Wire.endTransmission();
}

void Motion::inclination() {
	return request(0, MOTION_ADDRESS);
}

void Motion::request(byte data, byte address) {
  Wire.beginTransmission(address);
  Wire.write(data+127);
  Wire.endTransmission();
}
