/*
 * Enemy.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include <Ship.h>
#include "Bullet.h"

class Enemy: public Ship {
public:
	Enemy();
	virtual ~Enemy();

	int8_t (*dyfn)(int frames) = 0;

	int8_t dx, dy, fm, age;

	Bullet enemy_bullets[4];
};

#endif /* SRC_ENEMY_H_ */
