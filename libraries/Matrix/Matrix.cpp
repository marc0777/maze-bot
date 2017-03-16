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
    bool tDx = tempDx >= 20;
    bool tSx = tempSx >= 20;
    bool vicinoDx = distDx < 10;
    bool vicinoSx = distSx < 10;
    maze[floor][r][c].hot = tDx && vicinoDx || tSx && vicinoSx;
    if (color == 1) {
        checkr = r;
        checkc = c;
    }
}

void Matrix::changeFloor() {
    floor = !floor;
}

bool Matrix::guardaAvanti() { /// Restituisce vero se la cella davanti al bot è già stata visitata
    byte sr = r;
    byte sc = c;
    go();
    bool ris = maze[floor][r][c].visited;
    r = sr;
    c = sc;
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
