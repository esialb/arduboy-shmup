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

	uint8_t x_;
	uint8_t y_;
	bool active_;

	static const uint8_t BULLETS_SIZE = 6;
	Bullet bullets_[BULLETS_SIZE];

	void Draw();
};

#endif /* SRC_PLAYER_H_ */
