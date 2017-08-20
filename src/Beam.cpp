/*
 * Beam.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: robin
 */

#include <Beam.h>

#include "Constants.h"
#include "Externs.h"

void Beam::Fire() {
  if (beamf == 0 && engine.hp >= 50) {
    engine.hp += BEAM_COST_SCORE;
    beamf = 20;
  }
}

void Beam::BeamTone() {
  if (options.mute)
    return;
  static int freq = 2200;
  tones.tone(freq, 50);
  freq = freq / 1.3;
  if (freq < 300)
    freq = 2200;
}

void Beam::Tick() {
  if (beamf > 0) {
    BeamTone();
    beamf--;
    for (int i = 0; i < ENEMIES_SIZE; i++) {
      Enemy& e = enemies[i];
      if (e.active && e.x > player.x) {
        if (ShmupSprites::Collides(
            e.x, e.y, ShmupSprites::ENEMY_MASK,
            e.x, player.y, ShmupSprites::BEAM_MASK)) {
          e.active = false;
          engine.hp += DESTROY_ENEMY_SCORE;
        }
      }
      for (uint8_t j = 0; j < ENEMY_BULLETS_SIZE; j++) {
        Bullet& b = e.bullets[j];
        if (b.active
            && b.x > player.x) {
          if (ShmupSprites::Collides(
              b.x, b.y, ShmupSprites::BULLET_MASK,
              b.x, player.y, ShmupSprites::BEAM_MASK)) {
            b.active = false;
            engine.hp += DESTROY_BULLET_SCORE;
          }
        }
      }
    }
  }
}

void Beam::Draw() {
  if (beamf > 0) {
    arduboy.drawFastHLine(player.x + 8, player.y + 3, 128 - player.x - 8,
        BLACK);
    arduboy.drawFastHLine(player.x + 8, player.y + 4, 128 - player.x - 8,
        BLACK);
    int xoff = (4 + arduboy.frameCount % 4 - player.x % 4) % 4;
    int y = player.y + 3;
    for (int x = player.x + 8 + xoff; x < 128; x += 4)
      arduboy.drawPixel(x, y, WHITE);
    y++;
    for (int x = player.x + 8 + xoff + 1; x < 128; x += 4)
      arduboy.drawPixel(x, y, WHITE);

  }
}
