#include "Motion.h"

Motion::Motion () {
	Wire.begin();
}

void Motion::go() {
	setState(MOTION_FORWARD);
}

void Motion::go(bool invert) {
	setState((state)?MOTION_BACKWARD:MOTION_FORWARD);
}

void Motion::rotate() {
  setState(MOTION_RIGHT);
}

void Motion::rotate(bool invert) {
	setState((state)?MOTION_LEFT:MOTION_RIGHT);
}

void Motion::rotate(bool invert, bool infinite) {
	setState((infinite)?((state)?MOTION_LEFT_INFINITE:MOTION_RIGHT_INFINITE):((state)?MOTION_LEFT:MOTION_RIGHT));
}

void Motion::stop() {
	setState(MOTION_STOP);
}

void Motion::setState(byte state) {
	Wire.beginTransmission(MOTION_ADDRESS);
	Wire.write(state);
	Wire.endTransmission();  
}