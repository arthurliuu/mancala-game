#ifndef GAME_H
#define GAME_H

#include "Side.h"
#include "Player.h"
#include "Board.h"

class Game {

public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;

private:
	
	Board m_board;
	Player* first;
	Player* second;
	bool firstTurn;

};
#endif