#include <DistanceUS.h>
#include <Motion.h>

#define DISTWALL 7
#define TOLL 1
DistanceUS dist(40, 42);


int inclination;
bool turning = false;
Motion mov(&turning);

void receiveEvent(int howMany) {
  byte data = Wire.read();
  if (data == 255) turning = false;
  else inclination = data - 90;
}

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  short resto = (int)dist.read() % 30;
  if(resto > DISTWALL - TOLL && resto < DISTWALL + TOLL) Serial.println("STAMPO");
}

