#ifndef IMU_H
#define IMU_H

#include "IMU.h"
#include "ADXL345.h"
#include "Compass.h"
#include "EEPROM.h"

#define alpha 0.5

class IMU {
  public:
    void begin();
    void calibrate();
    float getRoll();
    float getPitch();
    float getYaw();
  private:
    void update();
    double filteredAcc[3];
    ADXL345 acc;
    Compass mag;
};
#endif
