#ifndef Cell_h
#define Cell_h

#define byte int

class Cell {
	private:
		byte data;
	public:
		Cell();
		bool isVisited();
		bool isHot();
		bool isBlack();
		byte getDirection();
		void visited();
		void hot();
		void black();
		void direction(byte dir);
};
#endif