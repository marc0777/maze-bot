#include "Cell.h"

Cell::Cell() {
	data=0;
}

bool Cell::isVisited() {
	return data & (1<<2);
}

bool Cell::isHot() {
	return data & (1<<1);
}

bool Cell::isBlack() {
	return data & 1;
}

byte Cell::getDirection() {
	return data & (7<<5);
}

void Cell::visited() {
	data|=1<<2;
}

void Cell::hot() {
	data|=1<<1;
}

void Cell::black() {
	data|=1;
}

void Cell::direction(data dir) {
	data|=dir<<5;
}