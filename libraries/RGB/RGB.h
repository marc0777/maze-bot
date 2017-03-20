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
    void crossFade(int color[3]);
    //Variables
    byte actual[3] = {0, 0, 0};
    byte pin[3];

    int black[3]  = { 0, 0, 0 };
    int white[3]  = { 100, 100, 100 };
    int red[3]    = { 100, 0, 0 };
    int green[3]  = { 0, 100, 0 };
    int blue[3]   = { 0, 0, 100 };
    int yellow[3] = { 40, 95, 0 };
    int dimWhite[3] = { 30, 30, 30 };

    int redVal = black[0];
    int grnVal = black[1];
    int bluVal = black[2];

    int previous[3] = {0, 0, 0};
};
#endif
