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
	sprite = Sprites::BULLET;
	mask = Sprites::BULLET_MASK;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::draw(Arduboy &arduboy) {
	if(active)
		Sprites::draw(arduboy, sprite, mask, x, y);
}
