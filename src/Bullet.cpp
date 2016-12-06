/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Bullet.h>
#include "Sprites.h"

Bullet::Bullet() {
	active = false;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::draw(Arduboy &arduboy) {
	if(active)
		Sprites::draw(arduboy, Sprites::BULLET, Sprites::BULLET_MASK, x, y);
}
