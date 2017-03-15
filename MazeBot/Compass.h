
#ifndef COMPASS_H
#define COMPASS_H

#include "Compass.h"

#define compass_address 0x1E       // The I2C address of the Magnetometer
#define compass_XY_excitation 1160 // The magnetic field excitation in X and Y direction during Self Test (Calibration)
#define compass_Z_excitation 1080  // The magnetic field excitation in Z direction during Self Test (Calibration)
#define compass_rad2degree 57.2957795131

#define compass_cal_x_offset 116   // Manually calculated offset in X direction
#define compass_cal_y_offset 225   // Manually calculated offset in Y direction
#define compass_cal_x_gain 1.1     // Stored Gain offset at room temperature
#define compass_cal_y_gain 1.12    // Stored Gain offset at room temperature

#define compass_debug FALSE

class Compass {
  public:
    float scaled[3];
    void read();
    void calibration(int select);
    void begin(int gain);
    void readScaled();
    typedef struct calVal {
      float offset[3] = {0.0, 0.0, 0.0};
      float gainError[3] = {1.0, 1.0, 0.0};
    } calVal;
    calVal calib;
  private:
    float gainFact = 1.0;
    float raw[3];
    int compass_debug;
};

#endif
