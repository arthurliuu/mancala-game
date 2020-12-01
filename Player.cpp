#include "Player.h"
#include <string>
#include <iostream>
#include <chrono>
#include <future>
#include <atomic>
#include <climits>
using namespace std;


Player::Player(std::string name) :m_name(name) {

}
std::string Player::name() const {
	return m_name;
}
bool Player::isInteractive() const {
	return false;
}

Player::~Player() {

}

HumanPlayer::HumanPlayer(std::string name) :Player(name) {

}
HumanPlayer::~HumanPlayer() {

}
bool HumanPlayer::isInteractive() const {
	return true;
}
int HumanPlayer::chooseMove(const Board& b, Side s) const {
	if (b.beansInPlay(s) == 0) {
		return -1;
	}
	int choice;
	cout << "Which hole? ";
	cin >> choice;
	while (choice > b.holes() || choice <= 0 || b.beans(s, choice) == 0) {
		cout << "Which hole? ";
		cin >> choice;
	}
	return choice;
}

BadPlayer::BadPlayer(std::string name) :Player(name) {

}
int BadPlayer::chooseMove(const Board& b, Side s) const {
	if (b.beansInPlay(s) == 0) {
		return -1;
	}
	int firstChoice;
	for (int i = 1; i <= b.holes(); i++) {
		if (b.beans(s, i) != 0) {
			firstChoice = i;
			break;
		}
	}
	return firstChoice;
}
BadPlayer::~BadPlayer() {

}

SmartPlayer::SmartPlayer(std::string name) :Player(name) {

}

int SmartPlayer::evaluate(const Board& b) const {
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0) {

		if (b.beansInPlay(NORTH) + b.beans(NORTH, 0) > b.beansInPlay(SOUTH) + b.beans(SOUTH, 0)) {
			return INT_MIN;
		}
		else if (b.beansInPlay(NORTH) + b.beans(NORTH, 0) < b.beansInPlay(SOUTH) + b.beans(SOUTH, 0)) {
			return INT_MAX;
		}
		else {
			return 0;
		}
	}
	else{//& b.beansInPlay(SOUTH) != 0) {
		int difference = b.beans(SOUTH, 0) - b.beans(NORTH, 0);
		return difference;
	}
}

int SmartPlayer::chooseMove(const Board& b, Side s) const {
	AlarmClock clock(4900);  // will time out after 4.9 seconds
	int depth = 6;
	int value = 0;
	int bestHole = 0;
	chooseSmartMove(b, s, depth, value, bestHole, clock);
	if (b.beans(s, bestHole) == 0)
		cerr << "didn't work";
	return bestHole;
}	

void SmartPlayer::chooseSmartMove(const Board& b, Side s, int &depthRef, int& valueRef, int& bestHoleRef, AlarmClock& ac) const {
	//check if no move for player exists AKA game is over
	Side endSide;
	int endHole = 0;
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0) {
		valueRef = evaluate(b);
		return;
	}
	//check if criterion says we should not search below this location
	if (depthRef == 0) {
		valueRef = evaluate(b);
		return;
	}
	//alarm clock base case
	if (ac.timedOut()) {
		valueRef = evaluate(b);
		return;
	}
	//create tree/branching
	Board copyBoard = b;
	int compare, garbagehole;
	bool initialized = false;
	//Board originalBoard = b;
	if (s == SOUTH) {
		for (int i = 1; i <= b.holes(); i++) {
			if (b.beans(SOUTH, i) == 0)
				continue;
			copyBoard.sow(SOUTH, i, endSide, endHole);
			if (endHole == 0) {
				chooseSmartMove(copyBoard, SOUTH, depthRef, compare, garbagehole, ac);
				//copyBoard = b;

			}
			else if (endSide == SOUTH && copyBoard.beans(SOUTH, endHole) == 1 && copyBoard.beans(NORTH, endHole) != 0 && endHole != 0) {
				copyBoard.moveToPot(NORTH, endHole, SOUTH); // south capture north
				copyBoard.moveToPot(SOUTH, endHole, SOUTH);
			}
			
			
			int a = depthRef-1;
			chooseSmartMove(copyBoard, NORTH, a, compare, garbagehole, ac);
			copyBoard = b;
			
			//depthRef++;

			if (!initialized) {
				valueRef = compare;
				initialized = true;
				bestHoleRef = i;
			}
			else if (compare > valueRef) {
				bestHoleRef = i;
				valueRef = compare;
			}
		}
		return;
	}
	if (s == NORTH) {
		for (int i = 1; i <= b.holes(); i++) {
			if (b.beans(NORTH, i) == 0)
				continue;
			copyBoard.sow(NORTH, i, endSide, endHole);
			if (endHole == 0) {
				chooseSmartMove(copyBoard, NORTH, depthRef, compare, garbagehole, ac);
				//copyBoard = b;
			}
			else if (endSide == NORTH && copyBoard.beans(NORTH, endHole) == 1 && copyBoard.beans(SOUTH, endHole) != 0 && endHole != 0) {
				copyBoard.moveToPot(NORTH, endHole, NORTH); // north capture south
				copyBoard.moveToPot(SOUTH, endHole, NORTH);
			}
			
			int a = depthRef-1;
			chooseSmartMove(copyBoard, SOUTH, a, compare, garbagehole, ac);
			copyBoard = b;
			
			//depthRef++;

			if (!initialized) {
				valueRef = compare;
				initialized = true;
				bestHoleRef = i;
			}
			else if (compare < valueRef) {
				bestHoleRef = i;
				valueRef = compare;
			}
		}
		return;
	}
	return;
}


SmartPlayer::~SmartPlayer() {

}


