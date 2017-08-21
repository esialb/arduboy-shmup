/*
 * Player.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: robin
 */

#include <Player.h>
#include "ShmupSprites.h"
#include "Constants.h"
#include "Externs.h"

Player::Player() {
  x = 0;
  y = 28;
  active = true;

  for (uint8_t i = 0; i < PLAYER_BULLETS_SIZE; i++) {
    bullets[i].dx = 2;
    bullets[i].dy = 0;
    bullets[i].fm = 1;
  }
}

Player::~Player() {
  // TODO Auto-generated destructor stub
}

void Player::Draw() {
  if (active)
    ShmupSprites::Draw(ShmupSprites::PLAYER, ShmupSprites::PLAYER_MASK, x, y);

  for (uint8_t i = 0; i < PLAYER_BULLETS_SIZE; i++)
    bullets[i].Draw();
  beam.Draw();
  for (int i = 0; i < WAVE_SIZE; i++)
    wave[i].Draw();
}

void Player::Fire() {
  if (weapon == 1)
    beam.Fire();
  if (weapon == 2) {
    for (int i = 0; i < WAVE_SIZE; i++) {
      if (!wave[i].active) {
        wave[i].Fire();
        break;
      }
    }
  }
}

void Player::Tick() {
  if (player.x > 0 && arduboy.pressed(LEFT_BUTTON))
    player.x--;
  if (player.x < WIDTH - 8 && arduboy.pressed(RIGHT_BUTTON))
    player.x++;
  if (player.y > 0 && arduboy.pressed(UP_BUTTON))
    player.y--;
  if (player.y < HEIGHT - 8 && arduboy.pressed(DOWN_BUTTON))
    player.y++;

  for (uint8_t i = 0; i < PLAYER_BULLETS_SIZE; i++) {
    if (player.bullets[i].active) {
      player.bullets[i].Tick();
    }
  }
  for (uint8_t i = 0; i < PLAYER_BULLETS_SIZE; i++) {
    if (player.bullets[i].active) {
      Bullet& b = player.bullets[i];
      if (b.active) {
        for (int j = 0; j < ENEMIES_SIZE; j++) {
          Enemy& e = enemies[j];
          if (e.active
              && ShmupSprites::Collides(b.x, b.y, ShmupSprites::BULLET_MASK,
                  e.x, e.y, ShmupSprites::ENEMY_MASK)) {
            e.active = false;
            b.active = false;
            engine.hp += DESTROY_ENEMY_SCORE;
            engine.score += DESTROY_ENEMY_SCORE + engine.level;
            if (!options.mute)
              tones.tone(800, 50);
            break;
          }
          bool nb = true;
          for (uint8_t k = 0; nb && k < ENEMY_BULLETS_SIZE; k++) {
            Bullet& b2 = e.bullets[k];
            if (b2.active
                && ShmupSprites::Collides(b.x, b.y,
                    ShmupSprites::BULLET_MASK, b2.x, b2.y,
                    ShmupSprites::BULLET_MASK)) {
              b2.active = false;
              b.active = false;
              engine.hp += DESTROY_BULLET_SCORE;
              engine.score += DESTROY_BULLET_SCORE;
              if (!options.mute)
                tones.tone(8800, 10);
              nb = false;
            }
          }
        }
      }
    }
  }

  beam.Tick();
  for (int i = 0; i < WAVE_SIZE; i++) {
    wave[i].Tick();
    wave[i].Collide();
  }

}

bool Player::Collides(int x, int y, const uint8_t* mask) {
  if (!active)
    return false;
  return ShmupSprites::Collides(this->x, this->y, ShmupSprites::PLAYER_MASK, x, y, mask);
}
