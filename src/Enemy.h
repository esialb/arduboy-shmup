/*
 * Enemy.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Bullet.h"

#include "Constants.h"

class Enemy {
public:
  Enemy();
  virtual ~Enemy();

  int8_t (*dyfn)(int frames) = 0;

  int8_t dx, dy, fm, age;

  uint8_t x;
  uint8_t y;bool active;

  Bullet bullets[ENEMY_BULLETS_SIZE];

  void Draw();
};

#endif /* SRC_ENEMY_H_ */
