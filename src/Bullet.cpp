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

void Bullet::draw() {
	if(active)
		ShmupSprites::draw(ShmupSprites::BULLET, ShmupSprites::BULLET_MASK, x, y);
}
