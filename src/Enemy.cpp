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

	bullets = enemy_bullets;
	bullets_size = 1;

	bullets[0].dx = -1;
	bullets[0].dy = 0;
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

