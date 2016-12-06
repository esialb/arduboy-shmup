/*
 * Ship.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Ship.h>

#include "Sprites.h"

Ship::Ship() {
	// TODO Auto-generated constructor stub

}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

void Ship::draw(Arduboy &arduboy) {
	Sprites::draw(arduboy, sprite, mask, x, y);
}
