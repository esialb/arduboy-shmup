/*
 * Enemy.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Bullet.h"

class Enemy {
public:
  Enemy();
  virtual ~Enemy();

  int8_t (*dyfn_)(int frames) = 0;

  int8_t dx_, dy_, fm_, age_;

  uint8_t x_;
  uint8_t y_;bool active_;

  static const uint8_t BULLETS_SIZE = 4;
  Bullet bullets_[BULLETS_SIZE];

  void Draw();
};

#endif /* SRC_ENEMY_H_ */
