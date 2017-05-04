#include "Ejector.h"
Ejector cagamattoni(6);
void setup() {
}

void loop() {
    if (!cagamattoni.isEmpty())
    cagamattoni.eject();
    delay(2000);
}

