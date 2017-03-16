struct Cella {
    bool visited = false;
    bool calda = false;
    bool salita = false;
    int direction = 0;
};

class Matrx {
public:
    Matrx() {}

    void verifica(int tempdx, int tempsx, int distdx, int distsx, int colore) { // TUTTO DA CHIARIRE
        maze[piano][i][j].visited = true;
        maze[piano][i][j].direction = dir;
        maze[piano][i][j].calda = tempdx > 68 || tempsx > 60; // Dovrebbe bastare questo altrimenti
        bool tDx = tempdx > 60;
        bool tSx = tempsx > 60;
        bool vicinoDx = distdx < 8;
        bool vicinoSx = distsx < 8;
        maze[piano][i][j].calda = tDx && vicinoDx || tSx && vicinoSx;
        if (colore == 1) {
            checki = i;
            checkj = j;
        }
    }

    bool guardAvanti() { /// Restituisce vero se la cella davanti al bot è già stata visitata
        short si = i, sj = j;
        avanti();
        bool ris = maze[piano][i][j].visited;
        i = si;
        j = sj;
        return ris;
    }

    void reset() {
        i = checki;
        j = checkj;
        dir = maze[piano][i][j].direction;
    }

    void avanti() {
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

    void gira(bool senso) /// Cambia direzione nella matrice (true = sinistra, false = destra)
    {
        if (senso)
            dir = dir == 0 ? 3 : dir - 1;
        else
            dir = dir == 3 ? 0 : dir + 1;
        maze[piano][i][j].direction = dir;
    }

    bool isCaldo() {
        return maze[piano][i][j].calda;
    }

    bool isVisited() {
        return maze[piano][i][j].visited;
    }

private:
    Cella maze[2][17][17];
    typedef unsigned char BYTE;
    BYTE piano = 0;
    short i = 8, j = 8; // parto dal centro, i = riga, j = colonna
    short dir = 0; // 0 = nord, 1 = est, 2 = sud, 3 = ovest
    short checki, checkj; // Coordinate dell'ultimo checkpoint

};