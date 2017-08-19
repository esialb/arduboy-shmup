/*
 * Enemy.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Enemy.h>

#include "ShmupSprites.h"

Enemy::Enemy() {
	age_ = 0;
	x_ = 0;
	y_ = 28;
	active_ = false;

	for(uint8_t i = 0; i < BULLETS_SIZE; i++) {
		bullets_[i].dx_ = -1;
		bullets_[i].dy_ = 0;
		bullets_[i].fm_ = 2;
	}

	dx_ = -1;
	dy_ = 0;
	fm_ = 3;
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

void Enemy::Draw() {
	if(active_)
		ShmupSprites::Draw(ShmupSprites::ENEMY, ShmupSprites::ENEMY_MASK, x_, y_);

	for(uint8_t i = 0; i < BULLETS_SIZE; i++)
		bullets_[i].Draw();
}

