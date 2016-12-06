/*
 * Enemy.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Enemy.h>

#include "Sprites.h"

Enemy::Enemy(int ex, int ey) {
	sprite = Sprites::ENEMY;
	mask = Sprites::ENEMY_MASK;
	x = ex;
	y = ey;
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

