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
#include "Beam.h"
#include "Wave.h"

#include "Constants.h"

class Player {
public:
  Player();
  virtual ~Player();

  void Tick();
  void Fire();
  bool Collides(int x, int y, const uint8_t* mask);

  uint8_t x;
  uint8_t y;bool active;

  Bullet bullets[PLAYER_BULLETS_SIZE];
  uint8_t weapon = 2;
  Beam beam;
  Wave wave[WAVE_SIZE];

  void Draw();
};

#endif /* SRC_PLAYER_H_ */
