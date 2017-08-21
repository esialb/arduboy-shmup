/*
 * Wave.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: robin
 */

#include <Wave.h>

#include "Externs.h"

void Wave::Fire() {
  if(ShmupEngine::hp + WAVE_COST_SCORE <= 0)
    return;
  if (active)
    return;
  ShmupEngine::hp += WAVE_COST_SCORE;
  active = true;
  x = player.x;
  y = player.y;
  age = 0;
  return;
}

void Wave::Draw() {
  if (active) {
    if (dx > 0)
      ShmupSprites::Draw(ShmupSprites::WAVE, ShmupSprites::WAVE_MASK, x, y);
    else if (dx < 0)
      ShmupSprites::Draw(ShmupSprites::EWAVE, ShmupSprites::EWAVE_MASK, x, y);
  }
}

void Wave::Tick() {
  if (age >= 64) {
    active = false;
  }
  if (x < 0 || x >= 120)
    active = false;
  if (!active)
    return;
  x += dx;
  age++;
}

void Wave::Collide() {
  if(!active)
    return;
  if (dx > 0) {
    for (Enemy& e : enemies) {
      if (e.Collides(x, y, ShmupSprites::WAVE_MASK)) {
        e.active = false;
        ShmupEngine::hp += DESTROY_ENEMY_SCORE;
        ShmupEngine::score += DESTROY_ENEMY_SCORE + ShmupEngine::level;
      }
      for (Bullet& b : e.bullets) {
        if (b.Collides(x, y, ShmupSprites::WAVE_MASK)) {
            b.active = false;
          ShmupEngine::hp += DESTROY_BULLET_SCORE;
          ShmupEngine::score += DESTROY_BULLET_SCORE;
        }
      }
    }

    if (age % 6 == 0)
      tones.tone(6000, 5);
  } else if (dx < 0) {
    if (player.Collides(x, y, ShmupSprites::EWAVE_MASK)) {
      ShmupEngine::collide = true;
    }
  }
}
