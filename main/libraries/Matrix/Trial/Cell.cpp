#include "Cell.h"

Cell::Cell() {
    data = 0;
}

bool Cell::isVisited() {
    return data & (1 << 2);
}

bool Cell::isHot() {
    return data & (1 << 1);
}

bool Cell::isBlack() {
    return data & 1;
}

byte Cell::getDirection() {
    return data & (7 << 5);
}

void Cell::visited() {
    data |= 1 << 2;
}

void Cell::hot() {
    data |= 1 << 1;
}

void Cell::black() {
    data |= 1;
}

void Cell::direction(byte dir) {
    data |= dir << 5;
}

void Cell::checkPoint() {
    data |= 1 << 3;
}

bool Cell::isCheckPoint() {
    return data & 1 << 3;
}

string Cell::toString() {
    string out = "";
    if (isBlack()) out = "B";
    else if (isHot()) out = "H";
    else if (isCheckPoint()) out = "@";
    else if (isVisited()) out = "-";
    return out;
}
