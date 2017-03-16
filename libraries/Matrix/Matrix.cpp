struct Cell {
    bool visited = false;
    bool hot = false;
    bool rise = false;
    int direction = 0;
};

class Matrix {
public:
    Matrix() {}
	
    void check(int tempdx, int tempsx, int distdx, int distsx, int color) { // TUTTO DA CHIARIRE
        maze[floor][i][j].visited = true;
        maze[floor][i][j].direction = dir;
        maze[floor][i][j].hot = tempdx > 68 || tempsx > 60; // Dovrebbe bastare questo altrimenti
        bool tDx = tempdx > 60;
        bool tSx = tempsx > 60;
        bool vicinoDx = distdx < 8;
        bool vicinoSx = distsx < 8;
        maze[floor][i][j].hot = tDx && vicinoDx || tSx && vicinoSx;
        if (color == 1) {
            checki = i;
            checkj = j;
        }
    }

    bool guardaAvanti() { /// Restituisce vero se la cella davanti al bot è già stata visitata
        short si = i, sj = j;
        go();
        bool ris = maze[floor][i][j].visited;
        i = si;
        j = sj;
        return ris;
    }

    void reset() {
        i = checki;
        j = checkj;
        dir = maze[floor][i][j].direction;
    }

    void go() {
        switch (dir) {
            case 0:
                i++;
                break;
            case 1:
                j++;
                break;
            case 2:
                i--;
                break;
            case 3:
                j--;
                break;
        }
    }

    void rotate(bool direction) /// Cambia direzione nella matrice (true = sinistra, false = destra)
    {
        if (direction)
            dir = dir == 0 ? 3 : dir - 1;
        else
            dir = dir == 3 ? 0 : dir + 1;
        maze[floor][i][j].direction = dir;
    }

    bool isHot() {
        return maze[floor][i][j].hot;
    }

    bool isVisited() {
        return maze[floor][i][j].visited;
    }

private:
    Cell maze[2][17][17];
    unsigned char byte;
    byte floor = 0;
    short i = 8, j = 8; // parto dal centro, i = riga, j = colonna
    short dir = 0; // 0 = nord, 1 = est, 2 = sud, 3 = ovest
    short checki, checkj; // Coordinate dell'ultimo checkpoint

};