#ifndef EJECTOR_H
#define EJECOR_H

#include <Arduino.h>

#define PIN1 3
#define PIN2 5
#define ENABLE 8

#define DELAY 869.56
#define MINDEL 200

class Ejector {
  public :
    Ejector(int ntappi);
    void eject();
    bool isEmpty();
    void turnOut();
    void turnIn();
    void stop();
  private :
    byte kits;
  
};

#endif
