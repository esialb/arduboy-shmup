/*
 * Ship.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Ship.h>

#include "ShmupSprites.h"

Ship::Ship() {
	// TODO Auto-generated constructor stub

}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

void Ship::draw(Arduboy2 &arduboy) {
	if(active)
		ShmupSprites::draw(arduboy, sprite, mask, x, y);

	for(int i = 0; i < bullets_size; i++)
		bullets[i].draw(arduboy);
}
