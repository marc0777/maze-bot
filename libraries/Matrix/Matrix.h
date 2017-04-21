#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>
#include "Cell.h"

#define DELTATEMP 10 // Delta minima di temperatorua perchè la parete sia calda
#define DISTWALL 10 // Distanza massima del robot dal muro vicino
#define NCELLS 31 // Numero totale di celle nel maze

class Matrix {
public:
    Matrix();

    /* Check the status of the cell (black, hot, checkpoint...)*/
    void check(float tempDx, float tempSx, float distDx, float distSx, float inclination, byte color);
    /* Change the floor of the matrix */
    void changeFloor();
    /* Returns true if the cell in front of the robot is already visited*/
    bool frontCheck();
    /* Returns true if the cell in front of the robot is black*/
    bool frontBlack();
    /* Move the position to the latest checkpoint*/
    void reset();
    /* Move the cursor in the cell in front of the robot */
    void go();
    /* Move the cursor in the cell behind the robot */
    void back();
    /* Returns the best direction */
    byte getDir(float dx, float front, float sx); // Ritorns 1 for indicate the rigth, 2 for the front, 3 for the left, 4 for the black
    /* Rotate the matrix cursor */
    void rotate(bool direction);
    /* Returns true if the current cell is hot */
    bool isHot();
    /* Returns true if the current cell is already visited */
    bool isVisited();

    bool keep; // This variable become false when the robot has finished the maze

private:
    Cell maze[2][19][19];
    bool floor;
    // Posizione attuale
    byte r[2];
    byte c[2];
    byte dir; // 0 = nord, 1 = est, 2 = sud, 3 = ovest
    // Latest checkpoint coordinates
    byte checkr;
    byte checkc;
    byte checkfl;
    bool rise; // True while the robot is rising
    int cont; // Visited cells counter
};

#endif //MATRIX_H
