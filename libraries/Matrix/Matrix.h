#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

class Matrix {
public:
    Matrix();

    void check(float tempDx, float tempSx, float distDx, float distSx, byte color);

    void changeFloor();

    bool frontCheck();

    bool frontBlack();

    void reset();

    void go();

    void back();

    void rotate(bool direction);

    bool isHot();

    bool isVisited();

private:
    typedef struct {
        bool visited;
        bool hot;
        bool rise;
        bool black;
        byte direction;
    } cell;
    cell maze[2][19][19];
    #define DELTATEMP 10
    #define DISTWALL 10
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
