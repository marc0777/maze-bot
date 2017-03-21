#include <Arduino.h>

#include <Wire.h>
#include <Moviment.h>

#define ADDRESS 7

byte state = 0;

Moviment mov(100,0,0);

void receiveEvent(int howMany) {
  state = Wire.read();
  mov.set(state);
}

void requestEvent() {
  Wire.write(mov.get());
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {

}
