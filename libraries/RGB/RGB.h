#ifndef RGB_h
#define RGB_h

#include <Arduino.h>

#define WAIT 5

class RGB {
  public:
    RGB(byte pinr, byte ping, byte pinb);
    void set(byte red, byte green, byte blue);
    void crossFade();
  private:
    void refresh();
    int calculateStep(int prevValue, int endValue);
    int calculateVal(int step, int val, int i);
    void crossFade(byte color[3]);
    //Variables
    byte pin[3];
    byte actual[3] = {0, 0, 0};
    byte previous[3] = {0, 0, 0};

    byte black[3]  = { 0, 0, 0 };
    byte white[3]  = { 100, 100, 100 };
    byte red[3]    = { 100, 0, 0 };
    byte green[3]  = { 0, 100, 0 };
    byte blue[3]   = { 0, 0, 100 };
    byte yellow[3] = { 40, 95, 0 };
    byte dimWhite[3] = { 30, 30, 30 };
};
#endif
