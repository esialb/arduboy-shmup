/*
 * Player.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Player.h>
#include "ShmupSprites.h"
#include "Constants.h"

Player::Player() {
	x = 0;
	y = 28;
	active = true;

	for(uint8_t i = 0; i < bullets_size; i++) {
		bullets[i].dx = 2;
		bullets[i].dy = 0;
		bullets[i].fm = 1;
	}
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::draw() {
	if(active)
		ShmupSprites::draw(ShmupSprites::PLAYER, ShmupSprites::PLAYER_MASK, x, y);

	for(uint8_t i = 0; i < bullets_size; i++)
		bullets[i].draw();
}
