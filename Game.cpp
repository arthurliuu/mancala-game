#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north):m_board(b),first(south), second(north), firstTurn(true) {

}

void Game::display() const {
	for (int i = 0; i < m_board.holes() - 1; i++) {
		cout << "  ";
	}
	cout << second->name() << endl << "  ";
	for (int i = 1; i <= m_board.holes(); i++) {
		cout << m_board.beans(NORTH, i) << "  ";
	}
	cout << endl << m_board.beans(NORTH, 0);
	for (int i = 1; i < m_board.holes() * 2; i++) {
		cout << "  ";
	}
	cout << m_board.beans(SOUTH, 0) << endl << "  ";
	for (int i = 1; i <= m_board.holes(); i++) {
		cout << m_board.beans(SOUTH, i) << "  ";
	}

	cout << endl;
	for (int i = 0; i < m_board.holes() - 1; i++) {
		cout << "  ";
	} 
	cout << first->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0) {
		over = true;
		if (m_board.beans(SOUTH, 0) > m_board.beans(NORTH, 0)) {
			hasWinner = true;
			winner = SOUTH;
		}
		else if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0)) {
			hasWinner = true;
			winner = NORTH;
		}
		else {
			hasWinner = false;
		}
	}
	else {
		over = false;
		return;
	}
}

bool Game::move() {
	bool over;
	bool hasWinner;
	Side winner;
	status(over, hasWinner, winner);
	
	if(!over) {
		int hole;
		Side endSide;
		int endHole;
		if (firstTurn) {
			hole = first->chooseMove(m_board, SOUTH);
			m_board.sow(SOUTH, hole, endSide, endHole); 
			if (endSide == SOUTH && endHole == 0 && m_board.beansInPlay(SOUTH) != 0) {
				display();
				cout << "Player gets another turn!" << endl;	
				move(); // another turn
			}
			else if (endSide == SOUTH && beans(SOUTH, endHole) == 1 && beans(NORTH, endHole) != 0 && endHole != 0) {
				m_board.moveToPot(NORTH, endHole, SOUTH); // south capture north
				m_board.moveToPot(SOUTH, endHole, SOUTH);
				display();
				cout << "capture!" << endl;
				firstTurn = false; // end of first turn
			
			}
			else {
				display();
				firstTurn = false;
				cout << "turn ends" << endl;
			
			}
			firstTurn = false;
			status(over, hasWinner, winner);
		}
		else if (!firstTurn){
			hole = second->chooseMove(m_board, NORTH);
			m_board.sow(NORTH, hole, endSide, endHole);
			if (endSide == NORTH && endHole == 0 && m_board.beansInPlay(NORTH) != 0) {
				display();
				cout << "Player gets another turn!" << endl;
				move(); // take another turn
			}
			else if (endSide == NORTH && beans(NORTH, endHole) == 1 && beans(SOUTH, endHole) != 0 && endHole != 0) {
				m_board.moveToPot(SOUTH, endHole, NORTH); // north capture south
				m_board.moveToPot(NORTH, endHole, NORTH);
				display();
				cout << "capture!" << endl;
				firstTurn = true; // end of second turn
				
			} else {
				display();
				firstTurn = true;
				cout << "turn ends" << endl;
				
			}
			firstTurn = true;
			status(over, hasWinner, winner);

		}		
	}
	if (over) {
		for (int i = 1; i <= m_board.holes(); i++) {
			m_board.moveToPot(NORTH, i, NORTH);
			m_board.moveToPot(SOUTH, i, SOUTH);
			
		}
		display(); // game is over
		return false;
	}

	return true;
}



void Game::play() {
	display();
	bool over = false;
	bool hasWinner = false;
	Side winner;
	string printWinner = "";
	status(over, hasWinner, winner);
	if ((first->isInteractive() == false) && (second->isInteractive() == false)) {
		while (!over) {
			cout << "Press enter to continue. ";
			cin.ignore(10000, '\n');
			move();
			status(over, hasWinner, winner);
			if (over) {
				if (winner == SOUTH) { 
					printWinner = first->name();
				}
				else if (winner == NORTH){
					printWinner = second->name();
					
				}
				else {
					cout << "tie!" << endl;
					return;
				}
				cout << "Winner is " << printWinner << endl;
				return;
			}
		}
	}
	else {
		while (!over) {
			move();
			status(over, hasWinner, winner); 
			if (over) {
				if (winner == SOUTH) {
					printWinner = first->name();
				}
				else if (winner == NORTH){
					printWinner = second->name();
				}
				else {
					printWinner = "tie";
				}
				cout << "Winner is " << printWinner << endl;
			}
		}
	}
	

}

int Game::beans(Side s, int hole) const {
	if (hole > m_board.holes()) {
		return -1;
	}
	if (s == NORTH) {
		return m_board.beans(NORTH, hole);
	}
	if (s == SOUTH) {
		return m_board.beans(SOUTH, hole);
	}
	return -1;
}
