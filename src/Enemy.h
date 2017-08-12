/*
 * Enemy.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Bullet.h"

class Enemy {
public:
	Enemy();
	virtual ~Enemy();

	int8_t (*dyfn)(int frames) = 0;

	int8_t dx, dy, fm, age;

	uint8_t x;
	uint8_t y;
	bool active;

	static const uint8_t bullets_size = 4;
	Bullet bullets[bullets_size];

	void draw(Arduboy2 &arduboy);
};

#endif /* SRC_ENEMY_H_ */
