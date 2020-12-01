#ifndef BOARD_H
#define BOARD_H

#include "Side.h"

class Board {

public:
	Board(int nHoles, int nInitialBeansPerHole);
	~Board();
	Board(const Board& b);
	Board& operator=(const Board& b);
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
private:
	void swap(Board& b);
	int m_holes;
	int* north;
	int* south;

};
#endif