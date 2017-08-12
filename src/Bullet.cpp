/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Bullet.h>
#include "ShmupSprites.h"

Bullet::Bullet() {
	active = false;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::draw(Arduboy2 &arduboy) {
	if(active)
		ShmupSprites::draw(arduboy, ShmupSprites::BULLET, ShmupSprites::BULLET_MASK, x, y);
}
