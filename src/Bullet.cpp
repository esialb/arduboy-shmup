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
	sprite = ShmupSprites::BULLET;
	mask = ShmupSprites::BULLET_MASK;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::draw(Arduboy2 &arduboy) {
	if(active)
		ShmupSprites::draw(arduboy, sprite, mask, x, y);
}
