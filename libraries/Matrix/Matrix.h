#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

class Matrix {
public:
    Matrix();

    void check(float tempDx, float tempSx, float distDx, float distSx, byte color);

    void changeFloor();

    bool guardaAvanti();

    void reset();

    void go();

    void rotate(bool direction);

    bool isHot();

    bool isVisited();

private:
    typedef struct {
        bool visited;
        bool hot;
        bool rise;
        byte direction;
    } cell;
    cell maze[2][17][17];
    bool floor;
    // Posizione attuale
    byte r;
    byte c;
    byte dir; // 0 = nord, 1 = est, 2 = sud, 3 = ovest
    // Coordinate dell'ultimo checkpoint
    byte checkr;
    byte checkc;
};

#endif //MATRIX_H
