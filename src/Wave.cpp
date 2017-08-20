/*
 * Wave.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: robin
 */

#include <Wave.h>

#include "Externs.h"

void Wave::Fire() {
  if (wait) {
    wait--;
    return;
  }
  for (uint8_t i = 0; i < WAVE_SIZE; i++) {
    if (active[i])
      continue;
    active[i] = true;
    x[i] = player.x;
    y[i] = player.y;
    wait = 10;
    return;
  }
}

void Wave::Draw() {
  for (uint8_t i = 0; i < WAVE_SIZE; i++) {
    if (active[i])
      ShmupSprites::Draw(ShmupSprites::WAVE, ShmupSprites::WAVE_MASK, x[i], y[i]);
  }

}

void Wave::Tick() {
  for (uint8_t w = 0; w < WAVE_SIZE; w++) {
    if (x[w] >= 120) {
      active[w] = false;
    }
    if (!active[w])
      continue;
    x[w]++;

    for (int i = 0; i < ENEMIES_SIZE; i++) {
      Enemy& e = enemies[i];
      if (e.active && e.x > player.x) {
        if (ShmupSprites::Collides(
            e.x, e.y, ShmupSprites::ENEMY_MASK,
            x[w], y[w], ShmupSprites::WAVE_MASK)) {
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
              x[w], y[w], ShmupSprites::WAVE_MASK)) {
            b.active = false;
            engine.hp += DESTROY_BULLET_SCORE;
            engine.score += DESTROY_BULLET_SCORE;
          }
        }
      }
    }
  }
}
