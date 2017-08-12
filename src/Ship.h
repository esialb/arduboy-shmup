/*
 * Ship.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_

#include <Arduboy2.h>
#include "Bullet.h"

class Ship {
public:
	Ship();
	virtual ~Ship();

	const unsigned char *sprite;
	const unsigned char *mask;

	uint8_t x;
	uint8_t y;
	bool active;

	Bullet *bullets;
	size_t bullets_size;

	void draw(Arduboy2 &arduboy);
private:
};

#endif /* SRC_SHIP_H_ */
