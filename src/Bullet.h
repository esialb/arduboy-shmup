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

  bool active_ = false;

  uint8_t x = 0, y = 0;
  int8_t dx = 0, dy = 0, fm = 0;
};

#endif /* SRC_BULLET_H_ */
