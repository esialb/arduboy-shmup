/*
 * Player.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Player.h>
#include "Sprites.h"

Player::Player() {
	sprite = Sprites::PLAYER;
	mask = Sprites::PLAYER_MASK;
	x = 0;
	y = 28;
	active = true;

	bullets = player_bullets;
	bullets_size = 3;

	for(int i = 0; i < bullets_size; i++) {
		bullets[i].dx = 2;
		bullets[i].dy = 0;
		bullets[i].fm = 1;
	}
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

