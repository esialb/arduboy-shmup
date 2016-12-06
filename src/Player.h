/*
lll * Player.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <Ship.h>

class Player: public Ship {
public:
	Player();
	virtual ~Player();

	Bullet player_bullets[3];
};

#endif /* SRC_PLAYER_H_ */
