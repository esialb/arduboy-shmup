/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Bullet.h>
#include "ShmupSprites.h"

#include "Constants.h"

Bullet::Bullet() {
  active_ = false;
}

Bullet::~Bullet() {
  // TODO Auto-generated destructor stub
}

void Bullet::Draw() {
  if (active_)
    ShmupSprites::Draw(ShmupSprites::BULLET, ShmupSprites::BULLET_MASK, x_, y_);
}

void Bullet::Tick() {
  if (arduboy_.frameCount % fm_ == 0) {
    x_ += dx_;
    y_ += dy_;
  }
  if (x_ <= -8 || x_ >= 128 || y_ <= -8 || y_ >= 64)
    active_ = false;
}
