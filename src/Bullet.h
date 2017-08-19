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

	void Draw();

	void Tick();

	bool active_;

	uint8_t x_, y_;
	int8_t dx_, dy_, fm_;
};

#endif /* SRC_BULLET_H_ */
