#include "L3G4200D.h"

bool L3G4200D::begin(l3g4200d_dps_t scale, l3g4200d_odrbw_t odrbw) {
  // Reset calibrate values
  for(int i = 0; i<3; i++) data[i]=0;
  useCalibrate = false;

  // Reset threshold values
  for(int i = 0; i<3; i++) threshold[i]=0;
  actualThreshold = 0;

  Wire.begin();

  // Check L3G4200D Who Am I Register
  if (fastRegister8(L3G4200D_REG_WHO_AM_I) != 0xD3) return false;

  // Enable all axis and setup normal mode + Output Data Range & Bandwidth
  byte reg1 = 0x00;
  reg1 |= 0x0F; // Enable all axis and setup normal mode
  reg1 |= (odrbw << 4); // Set output data rate & bandwidh
  writeRegister8(L3G4200D_REG_CTRL_REG1, reg1);

  // Disable high pass filter
  writeRegister8(L3G4200D_REG_CTRL_REG2, 0x00);

  // Generata data ready interrupt on INT2
  writeRegister8(L3G4200D_REG_CTRL_REG3, 0x08);

  // Set full scale selection in continous mode
  writeRegister8(L3G4200D_REG_CTRL_REG4, scale << 4);

  switch (scale) {
    case L3G4200D_SCALE_250DPS:
      dpsPerDigit = .00875f;
      break;
    case L3G4200D_SCALE_500DPS:
      dpsPerDigit = .0175f;
      break;
    case L3G4200D_SCALE_2000DPS:
      dpsPerDigit = .07f;
      break;
    default:
      break;
  }

  // Boot in normal mode, disable FIFO, HPF disabled
  writeRegister8(L3G4200D_REG_CTRL_REG5, 0x00);
  
  return true;
}

// Get current scale
l3g4200d_dps_t L3G4200D::getScale(void) {
  return (l3g4200d_dps_t)((readRegister8(L3G4200D_REG_CTRL_REG4) >> 4) & 0x03);
}

// Get current output data range and bandwidth
l3g4200d_odrbw_t L3G4200D::getOdrBw(void) {
  return (l3g4200d_odrbw_t)((readRegister8(L3G4200D_REG_CTRL_REG1) >> 4) & 0x0F);
}

// Calibrate algorithm
void L3G4200D::calibrate(byte samples) {
  // Set calibrate
  useCalibrate = true;

  // Reset values
  float sum[3];
  for(int i = 0; i<3; i++) sum[i]=0;
  float sigma[3];
  for(int i = 0; i<3; i++) sigma[i]=0;

  // Read n-samples
  for (byte i = 0; i < samples; ++i) {
    readRaw();
	for(int i = 0; i<3; i++) sum[i]+=raw[i];
	for(int i = 0; i<3; i++) sigma[i] += raw[i] * raw[i];
    delay(5);
  }

  // Calculate delta vectors
  for(int i = 0; i<3; i++) data[i] = sum[i]/samples;

  // Calculate threshold vectors
  thresholdX = sqrt((sigmaX / samples) - (data[0] * data[0]));
  thresholdY = sqrt((sigmaY / samples) - (data[1] * data[1]));
  thresholdZ = sqrt((sigmaZ / samples) - (data[2] * data[2]));

  // If already set threshold, recalculate threshold vectors
  if (actualThreshold > 0) {
    setThreshold(actualThreshold);
  }
}

// Get current threshold value
byte L3G4200D::getThreshold(void) {
  return actualThreshold;
}

// Set treshold value
void L3G4200D::setThreshold(byte multiple) {
  if (multiple > 0) {
    // If not calibrated, need calibrate
    if (!useCalibrate) calibrate();

    // Calculate threshold vectors
    threshold[0] = thresholdX * multiple;
    threshold[1] = thresholdY * multiple;
    threshold[2] = thresholdZ * multiple;
  } 
  else {
    // No threshold
    for(int i = 0; i<3; i++) threshold[i]=0;
  }

  // Remember old threshold value
  actualThreshold = multiple;
}

// Write 8-bit to register
void L3G4200D::writeRegister8(byte reg, byte value) {
  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Fast read 8-bit from register
byte L3G4200D::fastRegister8(byte reg) {
  byte value;

  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.requestFrom(L3G4200D_ADDRESS, 1);
  value = Wire.read();
  Wire.endTransmission();

  return value;
}

// Read 8-bit from register
byte L3G4200D::readRegister8(byte reg) {
  byte value;

  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.requestFrom(L3G4200D_ADDRESS, 1);
  while (!Wire.available()) {};
  value = Wire.read();
  Wire.endTransmission();

  return value;
}

// L3G4200D Temperature sensor output change vs temperature: -1digit/degrCelsius (data representation: 2's complement).
// Value represents difference respect to a reference not specified value.
// So temperature sensor can be used to measure temperature variations: temperarture sensor isn't suitable to return absolute temperatures measures.
// If you run two sequential measures and differentiate them you can get temperature variation.
// This also means that two devices in the same temp conditions can return different outputs.
// Finally, you can use this info to compensate drifts due to temperature changes.
byte L3G4200D::readTemperature(void) {
  return readRegister8(L3G4200D_REG_OUT_TEMP);
}


Vector L3G4200D::readRaw() {
  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.write(L3G4200D_REG_OUT_X_L | (1 << 7));
  Wire.endTransmission();
  Wire.requestFrom(L3G4200D_ADDRESS, 6);

  while (Wire.available() < 6);

  byte xla = Wire.read();
  byte xha = Wire.read();
  byte yla = Wire.read();
  byte yha = Wire.read();
  byte zla = Wire.read();
  byte zha = Wire.read();

  r.XAxis = xha << 8 | xla;
  r.YAxis = yha << 8 | yla;
  r.ZAxis = zha << 8 | zla;

  return r;
}

Vector L3G4200D::readNormalize() {
  readRaw();
  if (useCalibrate) {
    x = (raw[0] - data[0]) * dpsPerDigit;
    y = (raw[1] - data[1]) * dpsPerDigit;
    z = (raw[2] - data[2]) * dpsPerDigit;
  }
  else{
    x = raw[0] * dpsPerDigit;
    y = raw[1] * dpsPerDigit;
    y = raw[2] * dpsPerDigit;
  }
  if (actualThreshold > 0) {
    if (abs(x) < t.XAxis) x = 0;
    if (abs(y) < t.YAxis) y = 0;
    if (abs(z) < t.ZAxis) z = 0;
  }
  return n;
}
