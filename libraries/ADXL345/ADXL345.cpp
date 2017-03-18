#include "ADXL345.h"

int ADXL345::writeRegister(byte reg_addr, int nbytes, byte *buffer) {
  int written_bytes;
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(reg_addr);
  written_bytes = Wire.write(buffer, nbytes);
  Wire.endTransmission();
  return written_bytes;
}

int ADXL345::readRegister(byte reg_addr, int nbytes, byte *buffer) {
  int idx = 0;
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345_ADDRESS, nbytes);
  while (Wire.available() && idx < nbytes) buffer[idx++] = Wire.read();
  return idx;
}

ADXL345::ADXL345() {
  Wire.begin();
  offset[0] = -20;
  offset[1] =  15;
  offset[2] = -23;
}

void ADXL345::begin() {
  byte data = 0x08;
  writeRegister(ADXL345_POWER, 1, &data);
}

void ADXL345::end() {
  byte data = 0x00;
  writeRegister(ADXL345_POWER, 1, &data);
}

void ADXL345::read() {
  byte buffer[6];
  readRegister(ADXL345_DATA, 6, buffer);
  x = ((buffer[0] + (buffer[1] << 8)) - offset[0]) / 256.0;
  y = ((buffer[2] + (buffer[3] << 8)) - offset[1]) / 256.0;
  z = ((buffer[4] + (buffer[5] << 8)) - offset[2]) / 256.0;
}

void ADXL345::setRange(range_t range) {
   writeRegister(ADXL345_DATA_FORMAT, 1, (byte *)&range);
}

void ADXL345::setZeroG(double x, double y, double z) {
  offset[0] = x * 256.0;
  offset[1] = y * 256.0;
  offset[2] = z * 256.0;
}
