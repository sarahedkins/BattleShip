/*
 * Board.h
 *
 *  Created on: Jul 20, 2014
 *      Author: sarah
 */

#ifndef BOARD_H_
#define BOARD_H_
#include "Ship.h"

class Board {
private:

public:
	static const int ROW = 10, COL = 10;
	char array1[ROW][COL];

	int randomNumber();
	void initBoard();
	char getArrSpot(int r, int c);
	void fillWithShips(Ship list[], int numships);
	bool isVertical();

	Board();
	virtual ~Board();
};

#endif /* BOARD_H_ */
