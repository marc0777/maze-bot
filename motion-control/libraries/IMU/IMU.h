#ifndef IMU_h
#define IMU_h

#include "MadgwickAHRS.h"
#include "L3G4200D.h"
#include "ADXL345.h"

#define REFRESH 50

class IMU {
  public:
    IMU();
    void begin();
    void calibrate();
    void start();
    float yaw();
    float pitch();
    float roll();
	float getAcc();
  private:
    void update();
    L3G4200D gyroscope;
    ADXL345 acc;
    Madgwick filter;
    unsigned long microsPerReading;
    unsigned long microsPrevious;
};

IMU::IMU() {
  microsPerReading = 1000000 / REFRESH;
}

void IMU::begin() {
  gyroscope.begin(L3G4200D_SCALE_250DPS, L3G4200D_DATARATE_100HZ_12_5);
  acc.begin();
}

void IMU::calibrate() {
  gyroscope.calibrate(255);
}

void IMU::start() {
  filter.begin(REFRESH);
  microsPrevious = micros();
}

void IMU::update() {
  unsigned long microsNow;
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {
    acc.read();
    gyroscope.read();
    filter.update(gyroscope.x, gyroscope.y, gyroscope.z, acc.x, acc.y, acc.z);
    microsPrevious+=microsPerReading;
  }
}

float IMU::yaw() {
  update();
  return filter.getYaw();
}

float IMU::pitch() {
  update();
  return filter.getPitch();
}

float IMU::roll() {
  update();
  return filter.getRoll();
}

float IMU::getAcc(){
	return acc.x;
}


#endif
