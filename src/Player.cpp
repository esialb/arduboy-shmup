/*
 * Player.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Player.h>
#include "ShmupSprites.h"
#include "Constants.h"

Player::Player() {
  x_ = 0;
  y_ = 28;
  active_ = true;

  for (uint8_t i = 0; i < BULLETS_SIZE; i++) {
    bullets_[i].dx_ = 2;
    bullets_[i].dy_ = 0;
    bullets_[i].fm_ = 1;
  }
}

Player::~Player() {
  // TODO Auto-generated destructor stub
}

void Player::Draw() {
  if (active_)
    ShmupSprites::Draw(ShmupSprites::PLAYER, ShmupSprites::PLAYER_MASK, x_, y_);

  for (uint8_t i = 0; i < BULLETS_SIZE; i++)
    bullets_[i].Draw();
}
