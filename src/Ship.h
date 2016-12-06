/*
 * Ship.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_

#include <Arduboy.h>
#include "Bullet.h"

class Ship {
public:
	Ship();
	virtual ~Ship();

	const unsigned char *sprite;
	const unsigned char *mask;

	int x;
	int y;

	Bullet *bullets;
	size_t bullets_size;

	void draw(Arduboy &arduboy);
private:
};

#endif /* SRC_SHIP_H_ */
