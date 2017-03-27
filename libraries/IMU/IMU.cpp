#include <IMU.h>

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
