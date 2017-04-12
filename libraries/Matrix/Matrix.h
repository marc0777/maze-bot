#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>
#include "Cell.h"

#define DELTATEMP 10
#define DISTWALL 10
#define NCELLS 31

class Matrix {
public:
    Matrix();

    /// Check the status of the cell (black, hot, checkpoint...)
    void check(float tempDx, float tempSx, float distDx, float distSx, float inclination, byte color);
    /// Change the floor of the matrix
    void changeFloor();
    /// Return true if the cell in front of the robot is already visited
    bool frontCheck();
    /// Return true if the cell in front of the robot is black
    bool frontBlack();
    /// Move the position to the latest checkpoint
    void reset();

    void go();

    void back();

    byte getDir(float dx, float front, float sx);  /// Ritorna 1 per destra, 2 per avanti, 3 per sinistra, 4 dietro

    void rotate(bool direction);

    bool isHot();

    bool isVisited();

    bool keep;

private:
    // typedef struct {
    //   bool visited;
    //   bool hot;
    //   bool black;
    //   byte direction;
    // } cell;
    Cell maze[2][19][19];
    bool floor;
    // Posizione attuale
    byte r[2];
    byte c[2];
    byte dir; // 0 = nord, 1 = est, 2 = sud, 3 = ovest
    // Coordinate dell'ultimo checkpoint
    byte checkr;
    byte checkc;
    byte checkfl;
    bool rise;
    int cont;
};

#endif //MATRIX_H
