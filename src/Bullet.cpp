/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Bullet.h>
#include "ShmupSprites.h"

#include "Constants.h"

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

void Bullet::tick() {
	if(arduboy.frameCount % fm == 0) {
		x += dx;
		y += dy;
	}
	if(x <= -8 || x >= 128 || y <= -8 || y >= 64)
		active = false;
}
