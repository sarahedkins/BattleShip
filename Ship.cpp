/*
 * Ship.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: sarah
 */

#include "Ship.h"

Ship::Ship(int paramX, std::string name1, char id1) {
	// TODO Auto-generated constructor stub
	this->shipStatus = paramX;
	this->name = name1;
	this->id = id1;
}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

void Ship::takeAHit()
{
	this->shipStatus--;
}

bool Ship::didShipSink ()
{
	bool sank = false;
	if (this->shipStatus <= 0)
		sank = true;
	return sank;
}

int Ship::getShipStatus ()
{
	return this->shipStatus;
}

char Ship::getId()
{
	return this->id;
}

std::string Ship::getName()
{
	return this->name;
}
