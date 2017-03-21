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
}

void Motion::rotate(bool invert) {
	set((invert)?MOTION_LEFT:MOTION_RIGHT);
}

void Motion::rotate(bool invert, bool infinite) {
	set((infinite)?((invert)?MOTION_LEFT_INFINITE:MOTION_RIGHT_INFINITE):((invert)?MOTION_LEFT:MOTION_RIGHT));
}

void Motion::set(byte state) {
	Wire.beginTransmission(MOTION_ADDRESS);
	Wire.write(state);
	Wire.endTransmission();
}

byte Motion::get() {
	while (Wire.available()) Wire.requestFrom(MOTION_ADDRESS,1);
	byte state = Wire.read();
	return state;
}
