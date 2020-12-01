#include "Board.h"
using namespace std;
#include <iostream>


Board::Board(int nHoles, int nInitialBeansPerHole) {
	if (nHoles < 0) {
		nHoles = 1;
	} 
	if (nInitialBeansPerHole < 0) {
		nInitialBeansPerHole = 0;
	}
	m_holes = nHoles;
	
	north = new int[m_holes + 1];
	south = new int[m_holes + 1];
	north[0] = 0; // initialize pots
	south[0] = 0;
	for (int i = 1; i <= m_holes; i++) {
		north[i] = nInitialBeansPerHole; 
		south[i] = nInitialBeansPerHole;
	}
}

Board::Board(const Board& other) {
	m_holes = other.holes();

	north = new int[other.m_holes + 1];
	south = new int[other.m_holes + 1];

	north[0] = other.beans(NORTH, 0);
	south[0] = other.beans(SOUTH, 0);

	for (int i = 1; i <= other.m_holes; i++) {
		north[i] = other.beans(NORTH, i);
		south[i] = other.beans(SOUTH, i);
	}
}

Board& Board::operator=(const Board& other) { // assignment operator
	Board temp(other);
	swap(temp);
	return *this;
}
void Board::swap(Board& other) {
	int numHoles = other.m_holes; // switches head pointers and sizes
	int* tempNorth = other.north;
	int* tempSouth = other.south;
	other.north = north;
	other.south = south;
	other.m_holes = m_holes;
	north = tempNorth;
	south = tempSouth;
	m_holes = numHoles;
}

Board::~Board() {
	delete [] north;
	delete [] south;
}

int Board::holes() const {
	return m_holes;
}

int Board::beans(Side s, int hole) const {
	if (hole > m_holes) {
		return -1;
	}
	if (s == NORTH) {
		return north[hole];
	}
	if (s == SOUTH) {
		return south[hole];
	}
	return -1;
}

int Board::beansInPlay(Side s) const {
	int total = 0;
	if (s == NORTH) {
		for (int i = 1; i <= m_holes; i++) {
			total += north[i];
		}
	}
	else {
		for (int i = 1; i <= m_holes; i++) {
			total += south[i];
		}

	}
	return total;
}

int Board::totalBeans() const {
	int total = 0;
	for (int i = 0; i <= m_holes; i++) {
		total += north[i];
	}
	for (int i = 0; i <= m_holes; i++) {
		total += south[i];
	}
	return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) { 

	if (hole <= 0 || hole > m_holes || beans(s, hole) <= 0) {
		return false;
	}
	int number = beans(s, hole);
	if (s == SOUTH) {
		south[hole] = 0;
		while (number != 0) {
			for (int i = hole + 1; i <= m_holes; i++) {
				south[i] += 1;
				number--;
				if (number == 0) {
					endSide = SOUTH;
					endHole = i;
					return true;
				}
			}
			south[0] += 1;
			number--;
			if (number == 0) {
				endSide = SOUTH;
				endHole = 0;
				return true;
			}
			for (int i = m_holes; i > 0; i--) { // north side
				north[i] += 1;
				number--;
				if (number == 0) {
					endSide = NORTH;
					endHole = i;
					return true;
				}
			}
			for (int i = 1; i <= hole; i++) { // north side
				south[i] += 1;
				number--;
				if (number == 0) {
					endSide = SOUTH;
					endHole = i;
					return true;
				}
			}
		}

	}
	if (s == NORTH) {
		north[hole] = 0;
		while (number != 0) {
			for (int i = hole - 1; i > 0; i--) {
				north[i] += 1;
				number--;
				if (number == 0) {
					endSide = NORTH;
					endHole = i;
					return true;
				}
			}
			north[0] += 1;
			number--;
			if (number == 0) {
				endSide = NORTH;
				endHole = 0;
				return true;
			}
			for (int i = 1; i <= m_holes; i++) { // SOUTH side
				south[i] += 1;
				number--;
				if (number == 0) {
					endSide = SOUTH;
					endHole = i;
					return true;
				}
			}
			for (int i = m_holes; i >= hole; i--) {
				north[i] += 1;
				number--;
				if (number == 0) {
					endSide = NORTH;
					endHole = i;
					return true;
				}
			}
		}

	}
	return false;
}






bool Board::moveToPot(Side s, int hole, Side potOwner) {
	if (hole > m_holes || hole <= 0) {
		return false;
	}
	int number = beans(s, hole);
	if (potOwner == SOUTH) {
		if (s == SOUTH) {
			south[hole] = 0;
			south[0] += number;
			return true;
		} 
		if (s == NORTH) {
			north[hole] = 0;
			south[0] += number;
			return true;
		}
	}
	if (potOwner == NORTH) {
		if (s == NORTH) {
			north[hole] = 0;
			north[0] += number;
			return true;
		}
		if (s == SOUTH) {
			south[hole] = 0;
			north[0] += number;
			return true;
		}
	}
	return false;
}

bool Board::setBeans(Side s, int hole, int beans) {
	if (hole > m_holes || hole < 0 || beans < 0) {
		return false;
	}
	if (s == SOUTH) {
		south[hole] = beans;
		return true;
	}
	if (s == NORTH) {
		north[hole] = beans;
		return true;
	}
	return false;
}