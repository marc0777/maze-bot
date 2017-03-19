#include "Matrix.h"

Matrix::Matrix() {
    floor = 0;
    dir = 0;
    // parto dal centro
    r = 8;
    c = 8;
}

void Matrix::check(float tempDx, float tempSx, float distDx, float distSx, byte color) { /// Controlla lo stato della cella
    maze[floor][r][c].visited = true;
    maze[floor][r][c].direction = dir;
    /*maze[floor][r][c].hot = tempdx > 68 || tempsx > 60;*/
    bool hotDx = tempDx >= DELTATEMP && distDx < DISTWALL;
    bool hotSx = tempSx >= DELTATEMP && distSx < DISTWALL;
    maze[floor][r][c].hot = hotDx || hotSx;
    if (color == 1) {
        checkr = r;
        checkc = c;
    }else if(color == 2) maze[floor][r][c].black = true;
}

void Matrix::changeFloor() {
    floor = !floor;
}

bool Matrix::frontCheck() { /// Restituisce vero se la cella davanti al bot è già stata visitata
    go();
    bool ris = maze[floor][r][c].visited;
    back();
    return ris;
}

bool Matrix::frontBlack() { /// Restituisce vero se la cella davanti al bot è nera
    go();
    bool ris = maze[floor][r][c].black;
    back();
    return ris;
}

void Matrix::reset() {
    r = checkr;
    c = checkc;
    dir = maze[floor][r][c].direction;
}

void Matrix::go() {
    switch (dir) {
        case 0:
            r++;
            break;
        case 1:
            c++;
            break;
        case 2:
            r--;
            break;
        case 3:
            c--;
            break;
    }
}

void Matrix::back() {
    switch (dir) {
        case 0:
            r--;
            break;
        case 1:
            c--;
            break;
        case 2:
            r++;
            break;
        case 3:
            c++;
            break;
    }
}

byte Matrix::getDir() { /// Ritorna 1 per destra, 2 per avanti, 3 per sinistra, 4 dietro
  byte saved_dir = maze[floor][r][c].direction;
  byte dir = 0;
  bool found = false;
  rotate(false);
  if(!frontCheck && !frontBlack){

  }
}

void Matrix::rotate(bool direction) { /// Cambia direzione nella matrice (true = sinistra, false = destra)
    if (direction)
        dir = dir == 0 ? 3 : dir - 1;
    else
        dir = dir == 3 ? 0 : dir + 1;
    maze[floor][r][c].direction = dir;
}

bool Matrix::isHot() {
    return maze[floor][r][c].hot;
}

bool Matrix::isVisited() {
    return maze[floor][r][c].visited;
}
