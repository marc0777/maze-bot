#include "Cell.h"

Cell::Cell() {
	data=0;
}

bool Cell::isVisited() {
	return byte & (1<<2);
}

bool Cell::isHot() {
	return byte & (1<<1);
}

bool Cell::isBlack() {
	return byte & 1;
}

byte Cell::getDirection() {
	return byte & (7<<5);
}

void Cell::visited() {
	byte|=1<<2;
}

void Cell::hot() {
	byte|=1<<1;
}

void Cell::black() {
	byte|=1;
}

void Cell::direction(byte dir) {
	byte|=dir<<5;
}