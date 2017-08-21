/*
 * Wave.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: robin
 */

#include <Wave.h>

#include "Externs.h"

void Wave::Fire() {
  if (active)
    return;
  active = true;
  x = player.x;
  y = player.y;
  age = 0;
  return;
}

void Wave::Draw() {
  if (active)
    ShmupSprites::Draw(ShmupSprites::WAVE, ShmupSprites::WAVE_MASK, x, y);
}

void Wave::Tick() {
  if (age >= 64) {
    active = false;
  }
  if (!active)
    return;
  x++;
  age++;

  for (int i = 0; i < ENEMIES_SIZE; i++) {
    Enemy& e = enemies[i];
    if (e.active && e.x > player.x) {
      if (ShmupSprites::Collides(
          e.x, e.y, ShmupSprites::ENEMY_MASK,
          x, y, ShmupSprites::WAVE_MASK)) {
        e.active = false;
        engine.hp += DESTROY_ENEMY_SCORE;
        engine.score += DESTROY_ENEMY_SCORE;
      }
    }
    for (uint8_t j = 0; j < ENEMY_BULLETS_SIZE; j++) {
      Bullet& b = e.bullets[j];
      if (b.active
          && b.x > player.x) {
        if (ShmupSprites::Collides(
            b.x, b.y, ShmupSprites::BULLET_MASK,
            x, y, ShmupSprites::WAVE_MASK)) {
          b.active = false;
          engine.hp += DESTROY_BULLET_SCORE;
          engine.score += DESTROY_BULLET_SCORE;
        }
      }
    }
  }

  tones.tone((arduboy.frameCount % 2) ? 200 : 100, 10);
}
