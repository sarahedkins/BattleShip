// NOTES: Separate function, model view (outputs) and controller.

#include <iostream>
#include <fstream>
#include <string>
#include "Ship.h"
#include "Board.h"

using namespace std;

// declare constants
const int COL = 10; // number of columns on game board
const int ROW = 10; // number of rows on game board
const int NUMSHIPS = 5;

// prototypes
void getNewGuess(int&, int&);
Ship whichShip(char ship, Ship list1[]);
void checkAlreadyTried(bool& alreadyTried, int x, int y, int array1[][COL]);
void printHitStatement(string name);
void printMissStatement();
void printSankStatement(Ship myShip);
bool checkForShips(int num1);
void printWinningStatement(int);


// main
int main() {
// declare and initialize
	ifstream infile;
	int coX = -1, coY = -1;
	int i, j;
	int guesses[ROW][COL];
	bool gameOver = false;
	bool alreadyTried = false;
	bool sank = false;
	string shipName;
	Ship aircraft(5, "an aircraft carrier", 'A');
	Ship battleship(4, "a battleship", 'B');
	Ship submarine(3, "a submarine", 'S'), destroyer(3, "a destroyer", 'D');
	Ship patrolboat(2, "a patrol boat", 'P');
	Ship shipList[NUMSHIPS] = { aircraft, battleship, submarine, destroyer,
			patrolboat };
	Board gameBoard;
	int numOfGuesses = 0, numOfSunkenShips = 0;
	char guessedChar = 'X';

//// open file and check if it is open
//	infile.open("battleField.txt");
//	if (!infile) {
//		cout << "Error opening file.";
//		return 0;
//	}

// initialize board and fill with ships
gameBoard.initBoard();
gameBoard.fillWithShips(shipList, NUMSHIPS);

// initialize guesses to zero
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			guesses[i][j] = 0;

//// read in battle field
//	for (i = 0; i < ROW; i++)
//		for (j = 0; j < COL; j++)
//			infile >> field[i][j];

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

		numOfGuesses++;

		guessedChar = gameBoard.getArrSpot(coX, coY);

		if (guessedChar != 'O') {
// determines what ship, if any, was hit
			// variable shipInfo stores current ship
			Ship shipInfo = whichShip(guessedChar, shipList);

// prints a hit statement
			printHitStatement(shipInfo.getName());

// check if ship sank with previous hit
			sank = shipInfo.didShipSink();
			if (sank)
				{
				numOfSunkenShips++;
				printSankStatement(shipInfo);
				}

// check if there are still ships on the battlefield
gameOver = checkForShips(numOfSunkenShips);

// print a miss statement if no ship was hit
		} else
			printMissStatement();

	} while (!gameOver);

// print winning statement
	printWinningStatement(numOfGuesses);

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

Ship whichShip(char ship, Ship list1[]) {
	for (int i = 0; i < NUMSHIPS; i++)
		if (ship == list1[i].getId()) {
			list1[i].takeAHit();
			return list1[i];
		}
	return list1[0]; // should never hit this
}

void checkAlreadyTried(bool& alreadyTried, int x, int y, int array1[][COL]) {
	if (array1[x][y] == 1)
		alreadyTried = true;
	else {
		array1[x][y] = 1;
		alreadyTried = false;
	}
}

bool checkForShips(int num1)
{
	bool youWin = false;
	if (num1 == NUMSHIPS)
		youWin = true;
	return youWin;
}

// print statements
void printHitStatement(string name) {
	cout << "You hit " << name << "." << endl;
}

void printMissStatement() {
	cout << "Miss." << endl;
}

void printSankStatement(Ship myShip) {
	cout << "You sunk " << myShip.getName() << "!" << endl;
}

void printWinningStatement(int num1)
{
	cout << "Congratulations Comrade. You obliterated the sea!" << endl;
	cout << "You completed this mission in " << num1 << " rounds." << endl;

	if (num1 == 17)
		cout << "A perfect score! Couldn't have done better. Way to go!";
	else if (num1 > 17 && num1 <= 30)
		cout << "You are a strong leader. You rank among the top.";
	else if (num1 > 30 && num1 <=40)
		cout << "You aren't bad for a naval officer.";
	else if (num1 > 40 && num1 <=60)
		cout << "You need to sharpen your skills, mate.";
	else if (num1 > 60 && num1 <=80)
		cout << "Take this mop and start swabbing the decks.";
	else
		cout << "Let's hope they don't release the Kraken while you're on duty.";

	cout << endl;
}
