#include <Wire.h>

#define ADDRESS 7

byte state = 0;

void onReceive(int howMany) {
  state = Wire.read();
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(onReceive);
}

void loop() {
  
}
