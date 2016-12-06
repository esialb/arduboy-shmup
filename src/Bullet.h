/*
 * Bullet.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include <Arduboy.h>

class Bullet {
public:
	Bullet();
	virtual ~Bullet();

	void draw(Arduboy &arduboy);

	bool active;

	int x, y;
	int dx, dy, fm;

	unsigned char *sprite;
	unsigned char *mask;
};

#endif /* SRC_BULLET_H_ */
