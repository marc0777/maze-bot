#ifndef ADXL345_H
#define ADXL345_H

#include <Arduino.h>
#include <Wire.h>

#define ADXL345_ADDRESS 0x53
#define ADXL345_DATA_FORMAT 0x31
#define ADXL345_POWER 0x2D
#define ADXL345_DATA 0x32

typedef enum {
  RANGE_16G = 0x0B,
  RANGE_8G  = 0x0A,
  RANGE_4G  = 0x09,
  RANGE_2G  = 0x08
} range_t ;
    
class ADXL345 {
  public:
    ADXL345();
    void begin();
    void end();
    void read();
    void setRange(range_t range);
    void setZeroG(double x, double y, double z);
    float x, y, z;
  private:
    int offset[3];
    int readRegister(byte reg_addr, int nbytes, byte *buffer);
    int writeRegister(byte reg_addr, int nbytes, byte *buffer);
};

#endif // ADXL345_H
