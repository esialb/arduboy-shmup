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
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

