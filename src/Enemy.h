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

	Bullet enemy_bullets[1];
};

#endif /* SRC_ENEMY_H_ */
