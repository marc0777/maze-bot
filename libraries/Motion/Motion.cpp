#include "Motion.h"

Motion::Motion (bool *turning) {
	this->turning = turning;
}

void Motion::stop() {
	set(0);
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
	if (!infinite) {
		*turning=true;
		while(*turning) delay(1);
	}
}

void Motion::set(byte state) {
	send(state, MOTION_ADDRESS);
}

void Motion::inclination() {
	send(255, MOTION_ADDRESS);
}

void Motion::setSpeed(byte speed) {
	send(200+speed/5, MOTION_ADDRESS);
}

void Motion::send(byte data, byte address) {
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();
}
