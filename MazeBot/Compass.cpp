#include <Arduino.h>
#include <Wire.h>
#include "Compass.h"



void Compass::read() {
  Wire.beginTransmission(compass_address);
  Wire.write(0x02);
  Wire.write(0b10000001);
  Wire.endTransmission();
  Wire.requestFrom(compass_address, 6);
  if (6 <= Wire.available()) {
    raw[0] = Wire.read() << 8 | Wire.read();
    raw[2] = Wire.read() << 8 | Wire.read();
    raw[1] = Wire.read() << 8 | Wire.read();
  }
}
void Compass::calibration(int select) {
  if (select == 1 | select == 3) {
    Serial.println("Calibrating the Scolapasta....... Mestolacci!");
    Wire.beginTransmission(compass_address);
    Wire.write(0x00);
    Wire.write(0b01110001);
    Wire.endTransmission();
    read();
    while (raw[0] < 200 | raw[1] < 200 | raw[2] < 200) { // Making sure the data is with Positive baised
      read();
    }
    scaled[0] = raw[0] * gainFact;
    scaled[1] = raw[1] * gainFact;
    scaled[2] = raw[2] * gainFact;

    calib.gainError[0] = (float)compass_XY_excitation / scaled[0];
    calib.gainError[1] = (float)compass_XY_excitation / scaled[1];
    calib.gainError[2] = (float)compass_Z_excitation / scaled[2];

    Wire.beginTransmission(compass_address);
    Wire.write(0x00);
    Wire.write(0b01110010);
    Wire.endTransmission();


    read();
    while (raw[0] > -200 | raw[1] > -200 | raw[2] > -200) {
      read();
    }

    scaled[0] = raw[0] * gainFact;
    scaled[1] = raw[1] * gainFact;
    scaled[2] = raw[2] * gainFact;

    calib.gainError[0] = (float)((compass_XY_excitation / abs(scaled[0])) + calib.gainError[0]) / 2;
    calib.gainError[1] = (float)((compass_XY_excitation / abs(scaled[1])) + calib.gainError[1]) / 2;
    calib.gainError[2] = (float)((compass_Z_excitation / abs(scaled[2])) + calib.gainError[2]) / 2;

    Serial.print("x_gain_offset = ");
    Serial.println(calib.gainError[0]);
    Serial.print("y_gain_offset = ");
    Serial.println(calib.gainError[1]);
    Serial.print("z_gain_offset = ");
    Serial.println(calib.gainError[2]);
  }
  Wire.beginTransmission(compass_address);
  Wire.write(0x00);
  Wire.write(0b01111000);
  Wire.endTransmission();
  
  if (select == 2 | select == 3) { // User input in the function
    Serial.println("Calibrating the Magnetometer ....... Offset");
    Serial.println("Please rotate the magnetometer 2 or 3 times in complete circules with in one minute ............. ");

    for (byte i = 0; i < 10; i++) {
      read();
    }

    float x_max = -4000, y_max = -4000, z_max = -4000;
    float x_min = 4000, y_min = 4000, z_min = 4000;
    if (compass_debug) {
      Serial.println("Starting Debug data in ");
      delay(1000);
      Serial.println("3");
      delay(1000);
      Serial.println("2");
      delay(1000);
      Serial.println("1");
      delay(1000);
      Serial.println("0");
      Serial.println();
      for (byte i = 0; i < 10; i++) {
        Serial.print("*");
      }
      Serial.println("*");
      Serial.println("Debug -- (Offset Calibration)");
      for (byte i = 0; i < 10; i++) {
        Serial.print("*");
      }
      Serial.println("*");
    }
    unsigned long t = millis();
    while (millis() - t <= 30000) {

      read();

      scaled[0] = (float)raw[0] * gainFact * calib.gainError[0];
      scaled[1] = (float)raw[1] * gainFact * calib.gainError[1];
      scaled[2] = (float)raw[2] * gainFact * calib.gainError[2];

      if (compass_debug) { 
        Serial.print(scaled[0]);
        Serial.print("\t");
        Serial.print(scaled[1]);
        Serial.print("\t");
        Serial.println(scaled[2]);
      }
      
      x_max = max(x_max, scaled[0]);
      y_max = max(y_max, scaled[1]);
      z_max = max(z_max, scaled[2]);

      x_min = min(x_min, scaled[0]);
      y_min = min(y_min, scaled[1]);
      z_min = min(z_min, scaled[2]);
    }

    if (compass_debug) {
      Serial.println();
      for (byte i = 0; i < 10; i++) {
        Serial.print("*");
      }
      Serial.println("*");
      Serial.println("End Debug -- (Offset Calibration)");
      for (byte i = 0; i < 10; i++) {
        Serial.print("*");
      }
      Serial.println("*");
    }

    calib.offset[0] = ((x_max - x_min) / 2) - x_max;
    calib.offset[1] = ((y_max - y_min) / 2) - y_max;
    calib.offset[2] = ((z_max - z_min) / 2) - z_max;

    Serial.print("Offset x  = ");
    Serial.print(calib.offset[0]);
    Serial.println(" mG");
    Serial.print("Offset y  = ");
    Serial.print(calib.offset[1]);
    Serial.println(" mG");
    Serial.print("Offset z  = ");
    Serial.print(calib.offset[2]);
    Serial.println(" mG");
  }
}

void Compass::begin(int gain) {
  byte gain_reg, mode_reg;
  Wire.beginTransmission(compass_address);
  Wire.write(0x01);

  if (gain == 0) {
    gain_reg = 0b00000000;
    gainFact = 0.73;
  }
  else if (gain == 1) {
    gain_reg = 0b00100000;
    gainFact = 0.92;
  }
  else if (gain == 2) {
    gain_reg = 0b01000000;
    gainFact = 1.22;
  }
  else if (gain == 3) {
    gain_reg = 0b01100000;
    gainFact = 1.52;
  }
  else if (gain == 4) {
    gain_reg = 0b10000000;
    gainFact = 2.27;
  }
  else if (gain == 5) {
    gain_reg = 0b10100000;
    gainFact = 2.56;
  }
  else if (gain == 6) {
    gain_reg = 0b11000000;
    gainFact = 3.03;
  }
  else if (gain == 7) {
    gain_reg = 0b11100000;
    gainFact = 4.35;
  }

  Wire.write(gain_reg);
  Wire.write(0b00000011);
  Wire.endTransmission();

  Serial.print("Gain updated to  = ");
  Serial.print(gainFact);
  Serial.println(" mG/bit");

}

void Compass::readScaled() {
  read();
  scaled[0] = raw[0] * gainFact * calib.gainError[0] + calib.offset[0];
  scaled[1] = raw[1] * gainFact * calib.gainError[1] + calib.offset[1];
  scaled[2] = raw[2] * gainFact * calib.gainError[2] + calib.offset[2];

}



