#include "LibLum.h"
LibLum::LibLum(){}

/**
 * @return 0 se sotto non c'è niente, 1 se c'è uno specchio e 2 se è nero.
 */
int LibLum::surfaceType() { 
  int media = analogRead(R_CIR);
  delay(15);
  media += analogRead(L_CIR);
  media>>=1;  
  return (media <= MINBLACK)?((media >= MINMIRROR)?1:0):2;
}

