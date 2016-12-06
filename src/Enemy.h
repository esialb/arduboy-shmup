/*
 * Enemy.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include <Ship.h>

class Enemy: public Ship {
public:
	Enemy(int x, int y);
	virtual ~Enemy();
};

#endif /* SRC_ENEMY_H_ */
