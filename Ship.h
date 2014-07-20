/*
 * Ship.h
 *
 *  Created on: Jul 20, 2014
 *      Author: sarah
 */

#ifndef SHIP_H_
#define SHIP_H_
#include <string>

class Ship {

private:
	int shipStatus;
	std::string name;
	char id;

public:
	void takeAHit();
	bool didShipSink();
	char getId();
	std::string getName();

	Ship(int shipStatus, std::string name, char id);
	virtual ~Ship();
};

#endif /* SHIP_H_ */
