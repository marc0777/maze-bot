#include "RGB.h"

RGB::RGB(byte pinr, byte ping, byte pinb) {
  pin[0] = pinr;
  pin[1] = ping;
  pin[2] = pinb;
  for (int i = 0; i < 3; i++) pinMode(pin[i], OUTPUT);
}

void RGB::set(byte red, byte green, byte blue) {
  analogWrite(pin[0], red);
  analogWrite(pin[1], green);
  analogWrite(pin[2], blue);
}

void RGB::refresh() {
  set(actual[0], actual[1], actual[2]);
}

void RGB::crossFade() {
  crossFade(red);
  crossFade(green);
  crossFade(blue);
  crossFade(yellow);
}

void RGB::crossFade(byte color[3]) {
  for (int i = 0; i < 3; i++) color[i]=(color[i] * 255) / 100;
  int step[3];
  for (int i = 0; i < 3; i++) step[i] = calculateStep(previous[i], color[i]);
  for (int i = 0; i <= 1020; i++) {
    for (int j = 0; j < 3; j++) actual[j] = calculateVal(step[j], actual[j], i);
    refresh();
    delay(WAIT);
  }
  for (int i = 0; i < 3; i++) previous[i]=actual[i];
}

int RGB::calculateVal(int step, int val, int i) {
  if (step && i % step == 0) {
    if (step > 0) val += 1;
    else if (step < 0) val -= 1;
  }
  if (val > 255) val = 255;
  else if (val < 0) val = 0;
  return val;
}

int RGB::calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) step = 1020 / step;
  return step;
}
