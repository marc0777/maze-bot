#include "Matrix.h"

Matrix::Matrix() {
    floor = 0;
    dir = 0;
    // parto dal centro
    r = 8;
    c = 8;
}

void Matrix::check(int tempdx, int tempsx, int distdx, int distsx, int color) { // TUTTO DA CHIARIRE
    maze[floor][r][c].visited = true;
    maze[floor][r][c].direction = dir;
    Serial.println(sizeof(maze[floor][r][c]));
    maze[floor][r][c].hot = tempdx > 68 || tempsx > 60; // Dovrebbe bastare questo altrimenti
    /*bool tDx = tempdx > 60;
    bool tSx = tempsx > 60;
    bool vicinoDx = distdx < 8;
    bool vicinoSx = distsx < 8;
    maze[floor][r][c].hot = tDx && vicinoDx || tSx && vicinoSx; */
    if (color == 1) {
        checkr = r;
        checkc = c;
    }
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
