//
// Created by nicot on 16/03/2017.
//

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    Matrix();
    void check(int tempdx, int tempsx, int distdx, int distsx, int color);
    bool guardaAvanti();
    void reset();
    void go();
    void rotate(bool direction);
    bool isHot();
    bool isVisited();
private:
	typedef struct {
		bool visited;
		bool hot;
		bool rise;
		byte direction;
	} cell;
    cell maze[2][17][17];
    unsigned char byte;
    byte floor = 0;
	// Posizione attuale
    byte r; 
	byte c;
    byte dir; // 0 = nord, 1 = est, 2 = sud, 3 = ovest
	// Coordinate dell'ultimo checkpoint
    byte checkr; 
	byte checkc; 
};

#endif //MATRIX_H
