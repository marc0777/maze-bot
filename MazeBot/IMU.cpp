#include "IMU.h"


void IMU::begin()
{
  acc.begin();
  mag.begin(2);
  delay(100);
  EEPROM.get(0,mag.calib);
}

void IMU::update() {
  double reading[3];
  acc.read(&reading[0], &reading[1], &reading[2]);
  for (int i = 0; i < 3; i++) filteredAcc[i] = reading[i] * alpha + (filteredAcc[i] * (1.0 - alpha));
}

void IMU::calibrate() {
  digitalWrite(9,255);
  mag.calibration(3);
  EEPROM.put(0,mag.calib);
  digitalWrite(9,0);
}

float IMU::getRoll() {
  update();
  return (atan2(-filteredAcc[1], filteredAcc[2]) * 180.0) / PI;
}

float IMU::getPitch() {
  update();
  return (atan2(filteredAcc[0], sqrt(filteredAcc[1] * filteredAcc[1] + filteredAcc[2] * filteredAcc[2])) * 180.0) / PI;
}

float IMU::getYaw() {
  float yaw;
  mag.readScaled();
  if (mag.scaled[1] > 0) {
    yaw = 90 - atan(mag.scaled[0] / mag.scaled[1]) * compass_rad2degree;
  } else if (mag.scaled[1] < 0) {
    yaw = 270 - atan(mag.scaled[0] / mag.scaled[1]) * compass_rad2degree;
  } else if (mag.scaled[1] == 0 & mag.scaled[0] < 0) {
    yaw = 180;
  } else {
    yaw = 0;
  }
  return yaw;
}
