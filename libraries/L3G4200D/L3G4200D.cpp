#include "L3G4200D.h"

bool L3G4200D::begin(l3g4200d_dps_t scale, l3g4200d_odrbw_t odrbw)
{
  // Reset calibrate values
  d.XAxis = 0;
  d.YAxis = 0;
  d.ZAxis = 0;
  useCalibrate = false;

  // Reset threshold values
  t.XAxis = 0;
  t.YAxis = 0;
  t.ZAxis = 0;
  actualThreshold = 0;

  Wire.begin();

  // Check L3G4200D Who Am I Register
  if (fastRegister8(L3G4200D_REG_WHO_AM_I) != 0xD3)
  {
    return false;
  }

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

  switch (scale)
  {
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
l3g4200d_dps_t L3G4200D::getScale(void)
{
  return (l3g4200d_dps_t)((readRegister8(L3G4200D_REG_CTRL_REG4) >> 4) & 0x03);
}


// Get current output data range and bandwidth
l3g4200d_odrbw_t L3G4200D::getOdrBw(void)
{
  return (l3g4200d_odrbw_t)((readRegister8(L3G4200D_REG_CTRL_REG1) >> 4) & 0x0F);
}

// Calibrate algorithm
void L3G4200D::calibrate(byte samples)
{
  // Set calibrate
  useCalibrate = true;

  // Reset values
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  float sigmaX = 0;
  float sigmaY = 0;
  float sigmaZ = 0;

  // Read n-samples
  for (byte i = 0; i < samples; ++i)
  {
    readRaw();
    sumX += r.XAxis;
    sumY += r.YAxis;
    sumZ += r.ZAxis;

    sigmaX += r.XAxis * r.XAxis;
    sigmaY += r.YAxis * r.YAxis;
    sigmaZ += r.ZAxis * r.ZAxis;

    delay(5);
  }

  // Calculate delta vectors
  d.XAxis = sumX / samples;
  d.YAxis = sumY / samples;
  d.ZAxis = sumZ / samples;

  // Calculate threshold vectors
  thresholdX = sqrt((sigmaX / samples) - (d.XAxis * d.XAxis));
  thresholdY = sqrt((sigmaY / samples) - (d.YAxis * d.YAxis));
  thresholdZ = sqrt((sigmaZ / samples) - (d.ZAxis * d.ZAxis));

  // If already set threshold, recalculate threshold vectors
  if (actualThreshold > 0)
  {
    setThreshold(actualThreshold);
  }
}

// Get current threshold value
byte L3G4200D::getThreshold(void)
{
  return actualThreshold;
}

// Set treshold value
void L3G4200D::setThreshold(byte multiple)
{
  if (multiple > 0)
  {
    // If not calibrated, need calibrate
    if (!useCalibrate)
    {
      calibrate();
    }

    // Calculate threshold vectors
    t.XAxis = thresholdX * multiple;
    t.YAxis = thresholdY * multiple;
    t.ZAxis = thresholdZ * multiple;
  } else
  {
    // No threshold
    t.XAxis = 0;
    t.YAxis = 0;
    t.ZAxis = 0;
  }

  // Remember old threshold value
  actualThreshold = multiple;
}

// Write 8-bit to register
void L3G4200D::writeRegister8(byte reg, byte value)
{
  Wire.beginTransmission(L3G4200D_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Fast read 8-bit from register
byte L3G4200D::fastRegister8(byte reg)
{
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
byte L3G4200D::readRegister8(byte reg)
{
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
byte L3G4200D::readTemperature(void)
{
  return readRegister8(L3G4200D_REG_OUT_TEMP);
}

// Read raw values
Vector L3G4200D::readRaw()
{
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

// Read normalized values
Vector L3G4200D::readNormalize()
{
  readRaw();

  if (useCalibrate)
  {
    n.XAxis = (r.XAxis - d.XAxis) * dpsPerDigit;
    n.YAxis = (r.YAxis - d.YAxis) * dpsPerDigit;
    n.ZAxis = (r.ZAxis - d.ZAxis) * dpsPerDigit;
  } else
  {
    n.XAxis = r.XAxis * dpsPerDigit;
    n.YAxis = r.YAxis * dpsPerDigit;
    n.ZAxis = r.ZAxis * dpsPerDigit;
  }

  if (actualThreshold > 0)
  {
    if (abs(n.XAxis) < t.XAxis) n.XAxis = 0;
    if (abs(n.YAxis) < t.YAxis) n.YAxis = 0;
    if (abs(n.ZAxis) < t.ZAxis) n.ZAxis = 0;
  }

  return n;
}