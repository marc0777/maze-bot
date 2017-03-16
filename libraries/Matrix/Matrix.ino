#include "Matrix.h"

Matrix m;

void setup() {
    Serial.begin(9600);
    Serial.println(m.isVisited());
    m.go();
    m.rotate(true);
    m.go();
    m.check(70, 40, 7, 5, 1);
    Serial.println(m.isVisited());
    Serial.println(m.isHot());
    m.rotate(true);
    m.rotate(true);
    m.go();
    m.rotate(true);
    m.rotate(true);
    Serial.println(m.guardaAvanti());
}

void loop() {

}

