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

	int dx, dy, fm;

	Bullet enemy_bullets[2];
};

#endif /* SRC_ENEMY_H_ */
