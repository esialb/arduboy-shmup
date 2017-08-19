/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Bullet.h>
#include "ShmupSprites.h"

#include "Constants.h"
#include "Externs.h"

Bullet::Bullet() {
}

Bullet::~Bullet() {
  // TODO Auto-generated destructor stub
}

void Bullet::Draw() {
  if (active_)
    ShmupSprites::Draw(ShmupSprites::BULLET, ShmupSprites::BULLET_MASK, x, y);
}

void Bullet::Tick() {
  if (arduboy.frameCount % fm == 0) {
    x += dx;
    y += dy;
  }
  if (x <= -8 || x >= 128 || y <= -8 || y >= 64)
    active_ = false;
}
