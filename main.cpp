#include "Board.h"
#include "Player.h"
#include "Game.h"
#include "iostream"
#include <cassert>
using namespace std;

int main() {
	Board a(3, 2);
	assert(a.holes() == 3); // 3 
	assert(a.beans(NORTH, 1) == 2); // 2
	//for (int i = 0; i <= a.holes(); i++) { // 0222
	//	//cout << a.beans(NORTH, i);
	//}
	assert(a.beansInPlay(NORTH) == 6);
	assert(a.totalBeans() == 12);
	Side endSide;
	int endHole;
	//a.sow(NORTH, 1, endSide, endHole);
	//assert(a.beans(NORTH, 0) == 1); // 1
	//assert(a.beans(NORTH, 1) == 0); // 0
	//assert(a.beans(SOUTH, 1) == 3); // 3
	//assert(a.beans(SOUTH, 2) == 2); // 2 
	//assert(a.beans(SOUTH, 3) == 2); // 2
	//assert(a.beans(NORTH, 2) == 2); // 2
	//assert(a.beans(NORTH, 3) == 2); // 2
	//assert(a.beans(SOUTH, 0) == 0); // 0
	//assert(endSide == SOUTH && endHole == 1); // SOUTH  2

	Board b(3, 2);
	assert(b.sow(SOUTH, 3, endSide, endHole) == true);
	assert(b.beans(NORTH, 0) == 0); // 0
	assert(b.beans(NORTH, 1) == 2); // 2
	assert(b.beans(SOUTH, 1) == 2); // 2
	assert(b.beans(SOUTH, 2) == 2); // 2
	assert(b.beans(SOUTH, 3) == 0); // 0
	assert(b.beans(NORTH, 2) == 2); // 2
	assert(b.beans(NORTH, 3) == 3); // 3
	assert(b.beans(SOUTH, 0) == 1); // 1
	assert(endSide == NORTH && endHole == 3);


	Board c(6, 3);
	assert(c.sow(SOUTH, 2, endSide, endHole) == true);
	assert(c.beans(NORTH, 0) == 0); // 0
	assert(c.beans(NORTH, 1) == 3); // 3
	assert(c.beans(NORTH, 2) == 3); // 3
	assert(c.beans(NORTH, 3) == 3); // 3
	assert(c.beans(NORTH, 4) == 3); // 3
	assert(c.beans(NORTH, 5) == 3); // 3
	assert(c.beans(NORTH, 6) == 3); // 3
	assert(c.beans(SOUTH, 0) == 0); // 0
	assert(c.beans(SOUTH, 1) == 3); // 3
	assert(c.beans(SOUTH, 2) == 0); // 0
	assert(c.beans(SOUTH, 3) == 4); // 4
	assert(c.beans(SOUTH, 4) == 4); // 4
	assert(c.beans(SOUTH, 5) == 4); // 4
	assert(c.beans(SOUTH, 6) == 3); // 3
	assert(endSide == SOUTH && endHole == 5);
	
	

	Board d(6, 3);
	assert(d.sow(NORTH, 4, endSide, endHole) == true);
	assert(d.beans(NORTH, 0) == 0); // 0
	assert(d.beans(NORTH, 1) == 4); // 4
	assert(d.beans(NORTH, 2) == 4); // 4
	assert(d.beans(NORTH, 3) == 4); // 4
	assert(d.beans(NORTH, 4) == 0); // 0
	assert(d.beans(NORTH, 5) == 3); // 3
	assert(d.beans(NORTH, 6) == 3); // 3
	assert(d.beans(SOUTH, 0) == 0); // 0
	assert(d.beans(SOUTH, 1) == 3); // 3
	assert(d.beans(SOUTH, 2) == 3); // 3
	assert(d.beans(SOUTH, 3) == 3); // 3
	assert(d.beans(SOUTH, 4) == 3); // 3
	assert(d.beans(SOUTH, 5) == 3); // 3
	assert(d.beans(SOUTH, 6) == 3); // 3
	assert(endSide == NORTH && endHole == 1);

	assert(d.sow(SOUTH, 4, endSide, endHole) == true);
	assert(d.beans(NORTH, 0) == 0); // 0
	assert(d.beans(NORTH, 1) == 4); // 4
	assert(d.beans(NORTH, 2) == 4); // 4
	assert(d.beans(NORTH, 3) == 4); // 4
	assert(d.beans(NORTH, 4) == 0); // 0
	assert(d.beans(NORTH, 5) == 3); // 3
	assert(d.beans(NORTH, 6) == 3); // 3
	assert(d.beans(SOUTH, 0) == 1); // 1
	assert(d.beans(SOUTH, 1) == 3); // 3
	assert(d.beans(SOUTH, 2) == 3); // 3
	assert(d.beans(SOUTH, 3) == 3); // 3
	assert(d.beans(SOUTH, 4) == 0); // 0
	assert(d.beans(SOUTH, 5) == 4); // 4
	assert(d.beans(SOUTH, 6) == 4); // 4
	assert(endSide == SOUTH && endHole == 0);





	Board e(3, 9);
	assert(e.sow(SOUTH, 3, endSide, endHole) == true);
	assert(e.beans(NORTH, 0) == 0); // 0
	assert(e.beans(NORTH, 1) == 10); // 10
	assert(e.beans(NORTH, 2) == 10); // 10
	assert(e.beans(NORTH, 3) == 11); // 11
	assert(e.beans(SOUTH, 0) == 2); // 2
	assert(e.beans(SOUTH, 1) == 10); // 10
	assert(e.beans(SOUTH, 2) == 10); // 10
	assert(e.beans(SOUTH, 3) == 1); // 1
	assert(endSide == NORTH && endHole == 3);


	Board f(3, 9);
	f.sow(NORTH, 1, endSide, endHole);
	assert(f.beans(NORTH, 0) == 2); // 2
	assert(f.beans(NORTH, 1) == 1); // 1
	assert(f.beans(NORTH, 2) == 10); // 10
	assert(f.beans(NORTH, 3) == 10); // 10
	assert(f.beans(SOUTH, 0) == 0); // 0
	assert(f.beans(SOUTH, 1) == 11); // 11
	assert(f.beans(SOUTH, 2) == 10); // 10
	assert(f.beans(SOUTH, 3) == 10); // 10
	assert(f.beansInPlay(SOUTH) == 31); // 31
	assert(endSide == SOUTH && endHole == 1);
	assert(f.setBeans(SOUTH, 1, 20) == true);
	assert(f.beansInPlay(SOUTH) == 40);
	assert(f.totalBeans() == 63);
	assert(f.moveToPot(SOUTH, 1, SOUTH) == true);
	assert(f.beans(SOUTH, 0) == 20);
	assert(f.beans(SOUTH, 1) == 0);
	assert(f.totalBeans() == 63);
	assert(f.setBeans(NORTH, 1, 0) == true);
	assert(f.setBeans(SOUTH, 1, 2) == true);
	assert(f.setBeans(NORTH, 2, 0) == true);
	assert(f.setBeans(NORTH, 3, 0) == true);
	assert(f.setBeans(SOUTH, 34, 23) == false);

	Board bug(3, 2);
	bug.setBeans(NORTH, 1, 5);
	bug.setBeans(NORTH, 2, 0);
	bug.setBeans(NORTH, 3, 0);
	bug.setBeans(SOUTH, 1, 2);
	bug.setBeans(SOUTH, 2, 1);
	bug.setBeans(SOUTH, 3, 0);
	bug.sow(NORTH, 1, endSide, endHole);
	assert(bug.beans(NORTH, 3) == 1);
	
	
	Board best(5, 3);

	BadPlayer asdf("Michael");
	//asdf.chooseMove(f, NORTH);
	SmartPlayer jkl("Arthur");
	BadPlayer* asdff = &asdf;
	SmartPlayer* jkll = &jkl;
	//cout << jkl.chooseMove(f, NORTH) << endl;
	//cout << jkl.chooseMove(f, SOUTH) << endl;

	Game gg(best, asdff, jkll);
//	gg.display();
	//gg.move();
	//gg.move();
	gg.play();

	return 0;
}


//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//	BadPlayer bp1("Bart");
//	BadPlayer bp2("Homer");
//	Board b(3, 0);
//	b.setBeans(SOUTH, 1, 2);
//	b.setBeans(NORTH, 2, 1);
//	b.setBeans(NORTH, 3, 2);
//	Game g(b, &bp1, &bp2);
//	bool over;
//	bool hasWinner;
//	Side winner;
//	//    Homer
//	//   0  1  2
//	// 0         0
//	//   2  0  0
//	//    Bart
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//	g.move();
//	//   0  1  0
//	// 0         3
//	//   0  1  0
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//	g.move();
//	//   1  0  0
//	// 0         3
//	//   0  1  0
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//	g.move();
//	//   1  0  0
//	// 0         3
//	//   0  0  1
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//	g.move();
//	//   0  0  0
//	// 1         4
//	//   0  0  0
//	g.status(over, hasWinner, winner);
//	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//	assert(hasWinner && winner == SOUTH);
//}
//
//int main()
//{
//	doGameTests();
//	cout << "Passed all tests" << endl;
//}