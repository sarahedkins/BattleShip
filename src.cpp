// NOTES: Separate function, model view (outputs) and controller.

#include <iostream>
#include <fstream>
#include <string>
#include "Ship.h"

using namespace std;

// declare constants
const int COL = 10; // number of columns on game board
const int ROW = 10; // number of rows on game board
const int NUMSHIPS = 5;

// prototypes
void getNewGuess(int&, int&);
string whichShip(int x, int y, char array1[][COL], Ship list1[NUMSHIPS]);
string hitMiss(char char1);
void checkAlreadyTried(bool& alreadyTried, int x, int y, int array1[][COL]);
void printHitMiss(string name);

// main
int main() {
// declare and initialize
	ifstream infile;
	int coX = -1, coY = -1;
	int i, j;
	int guesses[ROW][COL];
	bool gameOver = false;
	bool alreadyTried = false;
	string shipName;
	char field[ROW][COL];
	Ship aircraft(5, "an aircraft carrier", 'A');
	Ship battleship(4, "a battleship", 'B');
	Ship submarine(3, "a submarine", 'S'), destroyer(3, "a destroyer", 'D');
	Ship patrolboat(2, "a patrol boat", 'P');
	Ship shipList[NUMSHIPS] = { aircraft, battleship, submarine, destroyer,
			patrolboat };

// open file and check if it is open
	infile.open("battleField.txt");
	if (!infile) {
		cout << "Error opening file.";
		return 0;
	}

// initialize guesses to zero
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			guesses[i][j] = 0;

// read in battle field
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			infile >> field[i][j];

// welcome message
	cout << "Welcome to Battle Ship." << endl;

	do {
// prompt user for pair of coordinates
		getNewGuess(coX, coY);

// check coordinates have not already been guessed
		checkAlreadyTried(alreadyTried, coX, coY, guesses);
		if (alreadyTried) {
			cout << "You've already tried this location." << endl;
			continue;
		}

// determines what ship, if any, was hit
		shipName = whichShip(coX, coY, field, shipList);

// prints a hit/miss statement
		printHitMiss(shipName);

	} while (!gameOver);

	return 0;
} // end main

// function definitions
void getNewGuess(int& coX, int& coY) {
	cout << "Enter your missile coordinates separated only by a space: ";
	cin >> coX >> coY;
	// adjust user input to match array index values;
	coX = coX - 1;
	coY = coY - 1;
}

string whichShip(int x, int y, char array1[][COL], Ship list1[NUMSHIPS]) {
	char obj_hit = array1[x][y];
	string miss = "water";
	for (int i = 0; i < NUMSHIPS; i++)
		if (obj_hit == list1[i].getId()) {
			list1[i].takeAHit();
			return list1[i].getName();
		}
	return miss;
}

void checkAlreadyTried(bool& alreadyTried, int x, int y, int array1[][COL]) {
	if (array1[x][y] == 1)
		alreadyTried = true;
	else {
		array1[x][y] = 1;
		alreadyTried = false;
	}
}

void printHitMiss(string name) {
	if (name != "water")
		cout << "You hit " << name << "." << endl;
	else
		cout << "Miss." << endl;
}
