/*
 * Player.h
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <Arduboy2.h>

#include "Bullet.h"

#include "Constants.h"

class Player {
public:
  Player();
  virtual ~Player();

  uint8_t x_;
  uint8_t y_;bool active_;

  Bullet bullets_[PLAYER_BULLETS_SIZE];

  void Draw();
};

#endif /* SRC_PLAYER_H_ */
