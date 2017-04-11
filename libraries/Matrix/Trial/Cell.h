#ifndef Cell_h
#define Cell_h

#define byte int

#include <iostream>

using namespace std;
class Cell {
private:
    byte data;

public:
    Cell();

    bool isVisited();

    bool isHot();

    bool isBlack();

    byte getDirection();

    void visited();

    void hot();

    void black();

    void direction(byte dir);

    void checkPoint();

    bool isCheckPoint();

    string toString();
};

#endif
