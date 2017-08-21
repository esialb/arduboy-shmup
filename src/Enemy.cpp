/*
 * Enemy.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Enemy.h>

#include "ShmupSprites.h"

#include "Externs.h"

int8_t curvy(int age) {
  age = age % 20;
  if (age < 5)
    return -age;
  if (age < 10)
    return -(10 - age);
  if (age < 15)
    return age - 10;
  return 20 - age;
}

int8_t jumpy_up(int age) {
  age = age % 12;
  if (age == 11)
    return 3;
  if (age == 10)
    return 2;
  if (age >= 6)
    return 1;
  if (age >= 4)
    return -1;
  return 0;
}

int8_t jumpy_down(int age) {
  return -jumpy_up(age);
}

Enemy::Enemy() {
  age = 0;
  x = 0;
  y = 28;
  active = false;

  for (uint8_t i = 0; i < ENEMY_BULLETS_SIZE; i++) {
    bullets[i].dx = -1;
    bullets[i].dy = 0;
    bullets[i].fm = 2;
  }

  dx = -1;
  dy = 0;
  fm = 3;

  wave.dx = -1;
}

Enemy::~Enemy() {
  // TODO Auto-generated destructor stub
}

void Enemy::Draw() {
  if (active)
    ShmupSprites::Draw(ShmupSprites::ENEMY, ShmupSprites::ENEMY_MASK, x, y);

  for (uint8_t i = 0; i < ENEMY_BULLETS_SIZE; i++)
    bullets[i].Draw();
  wave.Draw();
}

void Enemy::Tick() {
  if (!active) {
    if (random(0, 16) == 0) {
      if (engine.skip_spawn == 0) {
        x = 120;
        y = random(8, 64 - 16);
        active = true;
        fm = 2 + random(0, 3);
        dyfn = 0;
        age = 0;
        dy = 0;
        int ry = random(0, 5);
        if (ry == 0)
          dyfn = jumpy_down;
        else if (ry == 1)
          dyfn = jumpy_up;
        else if (ry == 2)
          dyfn = curvy;

        engine.skip_spawn = 3 + random(0, 6);
      } else
        engine.skip_spawn--;
    }
  }
  if (arduboy.frameCount % fm == 0) {
    x += dx;
    y += dy;
    age++;
    if (dyfn)
      dy = dyfn(age);
  }
  if (x <= -8 || x >= 128 || y <= -8 || y >= 64) {
    active = false;
  }
  for (uint8_t j = 0; j < ENEMY_BULLETS_SIZE; j++) {
    bullets[j].Tick();
  }
  for (uint8_t j = 0; j < ENEMY_BULLETS_SIZE; j++) {
    if (active && !bullets[j].active) {
      if (random(0, 90) != 0)
        continue;
      Bullet& b = bullets[j];
      b.active = true;
      b.x = x - 8;
      b.y = y;
      b.fm = fm - 1;
      break;
    }
  }
  if (active && random(0, 64) == 0 && !wave.active) {
    wave.active = true;
    wave.x = x;
    wave.y = y;
  }
  wave.Tick();

  for (uint8_t i = 0; i < ENEMIES_SIZE; i++) {
    Enemy& e = enemies[i];
    if (e.active) {
      if (ShmupSprites::Collides(player.x, player.y,
          ShmupSprites::PLAYER_MASK, e.x, e.y, ShmupSprites::ENEMY_MASK)) {
        engine.collide = true;
      }
    }
    for (uint8_t j = 0; j < ENEMY_BULLETS_SIZE; j++) {
      Bullet& b = e.bullets[j];
      if (!b.active)
        continue;
      if (ShmupSprites::Collides(player.x, player.y,
          ShmupSprites::PLAYER_MASK, b.x, b.y, ShmupSprites::BULLET_MASK)) {
        engine.collide = true;
      }
    }
  }

}
