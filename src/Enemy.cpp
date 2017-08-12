/*
 * Enemy.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Enemy.h>

#include "ShmupSprites.h"

Enemy::Enemy() {
	sprite = ShmupSprites::ENEMY;
	mask = ShmupSprites::ENEMY_MASK;
	x = 0;
	y = 28;
	active = false;

	bullets = enemy_bullets;
	bullets_size = 4;

	for(int i = 0; i < bullets_size; i++) {
		bullets[i].dx = -1;
		bullets[i].dy = 0;
		bullets[i].fm = 2;
	}

	dx = -1;
	dy = 0;
	fm = 3;
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

