#ifndef L3G4200D_h
#define L3G4200D_h

#include "Arduino.h"
#include <Wire.h>
#include <math.h>

#define ADDRESS 0x69
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define OUT 0x28
#define OUT_TEMP 0x26


typedef enum {
  L3G4200D_SCALE_2000DPS = 0b10,
  L3G4200D_SCALE_500DPS  = 0b01,
  L3G4200D_SCALE_250DPS  = 0b00
} l3g4200d_dps_t;

typedef enum {
  L3G4200D_DATARATE_800HZ_110  = 0b1111,
  L3G4200D_DATARATE_800HZ_50   = 0b1110,
  L3G4200D_DATARATE_800HZ_35   = 0b1101,
  L3G4200D_DATARATE_800HZ_30   = 0b1100,
  L3G4200D_DATARATE_400HZ_110  = 0b1011,
  L3G4200D_DATARATE_400HZ_50   = 0b1010,
  L3G4200D_DATARATE_400HZ_25   = 0b1001,
  L3G4200D_DATARATE_400HZ_20   = 0b1000,
  L3G4200D_DATARATE_200HZ_70   = 0b0111,
  L3G4200D_DATARATE_200HZ_50   = 0b0110,
  L3G4200D_DATARATE_200HZ_25   = 0b0101,
  L3G4200D_DATARATE_200HZ_12_5 = 0b0100,
  L3G4200D_DATARATE_100HZ_25   = 0b0001,
  L3G4200D_DATARATE_100HZ_12_5 = 0b0000
} l3g4200d_odrbw_t;

class L3G4200D {
  public:
	float x, y, z;
    bool begin(l3g4200d_dps_t scale = L3G4200D_SCALE_2000DPS, l3g4200d_odrbw_t odrbw = L3G4200D_DATARATE_100HZ_12_5);
    l3g4200d_dps_t getScale();
    l3g4200d_odrbw_t getOdrBw();
    void calibrate(byte samples = 50);
    void setThreshold(byte multiple = 1);
    byte getThreshold();
    void readRaw();
    void read();
    byte readTemperature();
  private:
    float raw[3];
    float threshold[3];
    float delta[3];
    bool useCalibrate;
    float actualThreshold;
    float dpsPerDigit;
    float thresholdX;
    float thresholdY;
    float thresholdZ;
	
    void writeRegister8(byte reg, byte value);
    byte readRegister8(byte reg);
    byte fastRegister8(byte reg);
};

#endif
