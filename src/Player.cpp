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
	bullets = player_bullets;
	bullets_size = 3;

	bullets[0].dx = 1;
	bullets[0].dy = 0;
	bullets[1].dx = 1;
	bullets[1].dy = 0;
	bullets[2].dx = 1;
	bullets[2].dy = 0;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

