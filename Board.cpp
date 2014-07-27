/*
 * Board.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: sarah
 */

#include "Board.h"
#include "Ship.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

Board::Board() {
	// constructor
}

Board::~Board() {
	//destructor
}

int Board::randomNumber() {
	int random_num;

	// initialize random seed
	srand(time(NULL));
	// generate random number number between 0 and 9
	random_num = rand() % 10;
	return random_num;
}

bool Board::isVertical() {
	return (Board::randomNumber() % 2 == 0);
}

void Board::initBoard() {
	for (int i = 0; i < Board::ROW; i++)
		for (int j = 0; j < Board::COL; j++)
			array1[i][j] = 'O';
}

char Board::getArrSpot(int r, int c)
{
	return array1[r][c];
}

void Board::fillWithShips(Ship list[], int numships) {
	int length, x, y;
	bool isVert = false;
	char shipChar = 'X';

	for (int i = 0; i < numships; i++) {
		bool Occupied = false;
		length = list[i].getShipStatus();
		shipChar = list[i].getId();

		myLabel:
		isVert = isVertical();
		x = randomNumber();
		y = randomNumber();

		if (isVert) {
			while ((10 - x) < length) {
				x--;
				if (array1[x][y] != 'O')
					Occupied = true;
			}
		}

		else {
			while ((10 - y) < length) {
				y--;
				if (array1[x][y] != 'O')
					Occupied = true;
			}
		}

		if (Occupied)
			goto myLabel;

		if (array1[x][y] == 'O')
			Board::array1[x][y] = shipChar;
		else
			goto myLabel;

		for (int j = 1; j < length; j++) {
			if (isVert) {
				x++;
				if (array1[x][y] == 'O')
					array1[x][y] = shipChar;
				else
					goto myLabel;
			} else
			{
				y++;
				if (array1[x][y] == 'O')
					array1[x][y] = shipChar;
				else
					goto myLabel;
			}
		}

	}

}
