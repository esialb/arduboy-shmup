/*
 * Bullet.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include <Arduboy2.h>

#include "ShmupSprites.h"

class Bullet {
public:
	Bullet();
	virtual ~Bullet();

	void draw();

	bool active;

	uint8_t x, y;
	int8_t dx, dy, fm;
};

#endif /* SRC_BULLET_H_ */
