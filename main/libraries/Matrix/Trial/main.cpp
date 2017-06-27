#include <iostream>
#include "Matrix.h"

#define byte int
using namespace std;
int r = 4, c = 7;
int sr = r, sc = c;
int dir = 0; // 0 = nord, 1 = est, 2 = sud, 3 = ovest


// '#' = muro, '-' = vuoto, 'B' = nero, '@' = checkpoint
char maze[7][11] =
        {
                {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                {'#', '-', '-', '-', '@', 'B', '#', '#', '#', '-', '#'},
                {'#', '-', '#', '#', '-', '-', '-', '-', '#', '-', '#'},
                {'#', '@', '-', '#', '-', '-', '#', '-', '-', '-', '#'},
                {'#', '-', '-', '#', '#', '#', '#', '@', '#', '-', '#'},
                {'#', '-', '-', '@', '-', '-', '-', '#', '-', '-', '#'},
                {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        };

void rotate(bool direction)   /// Cambia direzione nella matrice (true = sinistra, false = destra)
{
    if (direction)
        dir = dir == 0 ? 3 : dir - 1;
    else
        dir = dir == 3 ? 0 : dir + 1;
}

int readCol() {
    switch (maze[r][c]) {
        case 'B':
            return 2;
            break;
        case '@':
            return 1;
            break;
    }
    return 0;
}

void go() {
    switch (dir) {
        case 0:
            r--;
            break;
        case 1:
            c++;
            break;
        case 2:
            r++;
            break;
        case 3:
            c--;
            break;
    }
}

void back() {
    switch (dir) {
        case 0:
            r++;
            break;
        case 1:
            c--;
            break;
        case 2:
            r--;
            break;
        case 3:
            c++;
            break;
    }
}

float readAv() {
    go();
    float ris = maze[r][c] == '#' ? 8 : 20;
    back();
    return ris;
}

float readDX() {
    char val;
    switch (dir) {
        case 0:
            val = maze[r][c + 1];
            break;
        case 1:
            val = maze[r + 1][c];
            break;
        case 2:
            val = maze[r][c - 1];
            break;
        case 3:
            val = maze[r - 1][c];
            break;
    }

    return val == '#' ? 8 : 20;
}

float readSX() {
    char val;
    switch (dir) {
        case 0:
            val = maze[r][c - 1];
            break;
        case 1:
            val = maze[r - 1][c];
            break;
        case 2:
            val = maze[r][c + 1];
            break;
        case 3:
            val = maze[r + 1][c];
            break;
    }
    return val == '#' ? 8 : 20;
}

int main() {
    Matrix m;
    do {
        m.check(0, 0, readDX(), readSX(), 0, readCol());
        switch (m.getDir(readDX(), readAv(), readSX())) {
            case 1 :
                m.rotate(false);
                rotate(false);
                cout << "Gira a destra" << endl;
                break;
            case 3 :
                m.rotate(true);
                rotate(true);
                cout << "Gira a sinistra" << endl;
                break;
            case 4 :
                for (int i = 0; i < 2; i++) {
                    m.rotate(false);
                    rotate(false);
                }
                cout << "Gira all'indietro" << endl;
                break;
        }
        m.go();
        go();
        cout << "Avanti" << endl;
        if (readCol() == 2) {
            m.check(0, 0, 0, 0, 0, readCol());
            m.back();
            back();
            cout << "Visto nero, torna indietro" << endl;
        }
    } while (m.keep);
    m.printMaze("output.txt");
    return 0;
}
