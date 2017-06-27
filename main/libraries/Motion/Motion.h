#ifndef Motion_h
#define Motion_h

#include <Arduino.h>
#include <Wire.h>

#define MOTION_ADDRESS 7
#define MOTION_STOP 9
#define MOTION_FORWARD 1
#define MOTION_RIGHT 2
#define MOTION_BACKWARD 3
#define MOTION_LEFT 4
#define MOTION_RIGHT_INFINITE 5
#define MOTION_LEFT_INFINITE 6

class Motion {
  public:
    Motion(bool *turning);
    void stop();
    void go();
    void go(bool invert);
    void rotate();
    void rotate(bool invert);
    void rotate(bool invert, bool infinite);
    void set(byte state);
    void inclination();
    void setSpeed(byte speed);
  private:
  	bool *turning;
    void send(byte data, byte address);
};

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
  do {
  Wire.beginTransmission(address);
  Wire.write(data);;
  } while(Wire.endTransmission()!=0);
}

#endif
