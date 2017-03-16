#ifndef _ADXL345_H
#define _ADXL345_H

#include <Arduino.h>
#include <Wire.h>

#define ADDRESS 0x53
#define DATA_FORMAT 0x31
#define POWER_CTL 0x2D
#define DATAX0 0x32

class ADXL345
{
  private:
    int zG[3];
    int readRegister(byte reg_addr, int nbytes, byte *buffer);
    int writeRegister(byte reg_addr, int nbytes, byte *buffer);

  public:
    enum range_t
    {
      RANGE_16G = 0x0B,
      RANGE_8G  = 0x0A,
      RANGE_4G  = 0x09,
      RANGE_2G  = 0x08
    };
    
    float x, y, z;
    
    ADXL345();
    void begin();
    void end();
    void read();
    void setRange(range_t range);
    void setZeroG(double x, double y, double z);
};

#endif // _ADXL345_H
