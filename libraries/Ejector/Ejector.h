#ifndef EJECTOR_H
#define EJECOR_H

#include <Arduino.h>

#define PIN1 23
#define PIN2 24

#define DELAY 1000
#define MINDEL 50

class Ejector {
  public :
    Ejector(int ntappi);
    void eject();
    bool isEmpty();
  private :
    byte kits;
  
};

#endif
