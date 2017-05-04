#include <DistanceUS.h>
#include <Motion.h>

#define DISTWALL 24
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
  Wire.begin(8);
  Wire.onReceive(receiveEvent);  
  mov.go();
}

void loop() {
  short resto = ((int)dist.read()) % 30;
  if ((resto > DISTWALL - TOLL) && (resto < DISTWALL + TOLL)) {
    mov.stop();
    delay(2000);
    mov.go();
    do {
      resto = ((int)dist.read()) % 30;
    } while ((resto < DISTWALL + TOLL));
  }
}

