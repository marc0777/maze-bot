struct Cella {
	bool visited = false;
	bool calda = false;
	bool salita = false;
};
class Matrice {
public:
	Matrice() {

	}

	void verifica() {
		maze[i][j].visited = true;
		bool tDx = (tDestra.readObj() - tDestra.readAmb()) > 20;
		bool tSx = (tSinistra.readObj() - tSinistra.readAmb()) > 20;
		bool vicinoDx = US[0].read() < 8;
		bool vicinoSx = US[2].read() < 8;
		if (!maze[i][j].calda || tDx && vicinoDx || tSx && vicinoSx) {
			maze[i][j].calda = true;
		}
		if (tDx && !vicinoDx) {
			int ncelle = (int) US[0].read() % 30;
			short ti = i, tj = j, tdr = dir;
			gira(false);
			for (int k = 0; k < ncelle; k++)
				avanti();
			maze[i][j].calda = true;
			i = ti;
			j = tj;
			dir = tdr;
		}
		if (tSx && !vicinoSx) {
			int ncelle = (int) US[2].read() % 30;
			short ti = i, tj = j, tdr = dir;
			gira(true);
			for (int k = 0; k < ncelle; k++)
				avanti();
			maze[i][j].calda = true;
			i = ti;
			j = tj;
			dir = tdr;
		}
		// tDestra, tSinistra
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

	void gira(bool senso) { // true = sinistra, false = destra
		if (senso)
			dir = dir == 0 ? 3 : dir - 1;
		else
			dir = dir == 3 ? 0 : dir + 1;
	}

	bool isCaldo() {
		return maze[i][j].calda;
	}

	bool isVisited() {
		return maze[i][j].visited;
	}

private:
	Cella pianTerreno[17][17];
	Cella primoPiano[17][17];
	short i = 8, j = 8; // parto dal centro, i = riga, j = colonna
	short dir = 0; // 0 = nord, 1 = est, 2 = sud, 3 = ovest

};
