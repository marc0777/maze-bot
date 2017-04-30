#ifndef Motion_h
#define Motion_h

#include <Arduino.h>
#include <Wire.h>

#define MOTION_ADDRESS 7
#define MOTION_STOP 0
#define MOTION_FORWARD 1
#define MOTION_RIGHT 2
#define MOTION_BACKWARD 3
#define MOTION_LEFT 4
#define MOTION_RIGHT_INFINITE 5
#define MOTION_LEFT_INFINITE 6

class Motion {
  public:
    Motion();
    void stop();
    void go();
    void go(bool invert);
    void rotate();
    void rotate(bool invert);
    void rotate(bool invert, bool infinite);
    void set(byte state);
    byte get();
    int inclination();
  private:
    byte request();
};
#endif
