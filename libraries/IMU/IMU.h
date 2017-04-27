#ifndef IMU_h
#define IMU_h

#include <MadgwickAHRS.h>
#include <L3G4200D.h>
#include <ADXL345.h>

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
  private:
    void update();
    L3G4200D gyroscope;
    ADXL345 acc;
    Madgwick filter;
    unsigned long microsPerReading;
    unsigned long microsPrevious;
};

#endif

