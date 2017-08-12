/*
lll * Player.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <Arduboy2.h>

#include "Bullet.h"

class Player {
public:
	Player();
	virtual ~Player();

	uint8_t x;
	uint8_t y;
	bool active;

	static const uint8_t bullets_size = 4;
	Bullet bullets[bullets_size];

	void draw(Arduboy2 &arduboy);
};

#endif /* SRC_PLAYER_H_ */
