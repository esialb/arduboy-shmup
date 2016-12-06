/*
 * Enemy.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Enemy.h>

#include "Sprites.h"

Enemy::Enemy() {
	sprite = Sprites::ENEMY;
	mask = Sprites::ENEMY_MASK;
	x = 0;
	y = 28;
	active = false;

	bullets = enemy_bullets;
	bullets_size = 3;

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

