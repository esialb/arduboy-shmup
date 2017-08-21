/*
 * ShmupEngine.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: robin
 */

#include <ShmupEngine.h>

#include "ShmupSprites.h"

#include "Constants.h"
#include "Externs.h"

void ShmupEngine::CollisionTone() {
  if (options.mute)
    return;
  static int freq = 1100;
  tones.tone(freq, 50);
  freq *= 2;
  if (freq > 10000)
    freq = 1100;
}

void ShmupEngine::GameOverTone() {
  if (options.mute)
    return;
  tones.tone(440, 1000);
}

void ShmupEngine::WeaponCheck() {
  if (weapon_skip_fire > 0)
    weapon_skip_fire--;
  if (!arduboy.pressed(A_BUTTON))
    return;
  if (weapon_skip_fire > 0)
    return;
  weapon_skip_fire = 8;
  player.Fire();
}

void ShmupEngine::MenuCheck() {
  if (!arduboy.pressed(B_BUTTON))
    return;
  do {
    while (arduboy.pressed(B_BUTTON)) {
      arduboy.setCursor(0, 0);
      arduboy.setTextColor(WHITE);
      arduboy.setTextBackground(BLACK);
      switch(player.weapon) {
      case 0:
        arduboy.print("PAUSE ");
        break;
      case 1:
        arduboy.print("BEAM  ");
        break;
      case 2:
        arduboy.print("WAVE  ");
        break;
      }
      arduboy.display();
      if (arduboy.pressed(UP_BUTTON))
        player.weapon--;
      if (arduboy.pressed(DOWN_BUTTON))
        player.weapon++;
      while(arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON))
        ;
      if(player.weapon == 255)
        player.weapon = 2;
      if (player.weapon == 3)
        player.weapon = 0;
    }
  } while(player.weapon == 0);
  arduboy.setTextColor(BLACK);
  arduboy.setTextBackground(WHITE);
}

void ShmupEngine::GameOverCheck() {
  if (arduboy.pressed(B_BUTTON)) {
    while (arduboy.pressed(B_BUTTON))
      ;
    arduboy.invert(false);
    options.SelectOptions();
    gameover = false;
    player.x = 0;
    player.y = 28;
    player.active = true;
    for (uint8_t i = 0; i < PLAYER_BULLETS_SIZE; i++)
      player.bullets[i].active = false;
    for (uint8_t i = 0; i < ENEMIES_SIZE; i++) {
      enemies[i].x = 0;
      enemies[i].y = 28;
      enemies[i].active = false;
      for (uint8_t j = 0; j < ENEMY_BULLETS_SIZE; j++)
        enemies[i].bullets[j].active = false;
    }
    hp = 300;
    score = 0;
  }
}

void ShmupEngine::CollideCheck() {
  if (collide) {
    CollisionTone();
    if (!inverting) {
      arduboy.invert(true);
      inverting = true;
      hp += PLAYER_HIT_SCORE;
    }
  } else {
    inverting = false;
    arduboy.invert(false);
  }
}

void ShmupEngine::EnemiesUpdate() {
  for (uint8_t i = 0; i < ENEMIES_SIZE; i++) {
    Enemy& e = enemies[i];
    e.Tick();
  }
}

void ShmupEngine::Tick() {
  if (!arduboy.nextFrame())
    return;
  collide = false;

  if (gameover) {
    GameOverCheck();
    return;
  }

  player.Tick();

  WeaponCheck();

  MenuCheck();

  if (skip_fire == 0) {
    for (uint8_t i = 0; i < PLAYER_BULLETS_SIZE; i++) {
      Bullet& b = player.bullets[i];
      if (b.active)
        continue;
      b.active = true;
      b.x = player.x + 8;
      b.y = player.y;
      break;
    }
    skip_fire = 10;
  } else
    skip_fire--;

  EnemiesUpdate();

  CollideCheck();

  if (hp < 0) {
    GameOverTone();
    gameover = true;
  }

  if (hp < 0)
    arduboy.setRGBled(0, 0, 0);
  else if (hp < 100)
    arduboy.setRGBled(255, 0, 0);
  else if (hp < 200)
    arduboy.setRGBled(255, 255, 0);
  else
    arduboy.setRGBled(0, 0, 0);
}

void ShmupEngine::Draw() {
  arduboy.fillScreen(WHITE);

  arduboy.drawFastHLine(0, 7, 128, BLACK);
  char buf[16];
  itoa(hp / 100, buf, 10);
  ShmupSprites::DrawInt(hp / 100, 128 - 4 * strlen(buf), 1);
  ShmupSprites::DrawInt(score, 1, 1);

  //	char buf[12];
  //	itoa(score, buf, 10);
  //	arduboy.setCursor(0, 0);
  //	arduboy.print(buf);

  int lh = 31 - ((arduboy.frameCount >> 3) & 0x1F);
  arduboy.drawFastVLine(lh, 7, 57, BLACK);
  arduboy.drawFastVLine(32 + lh, 7, 57, BLACK);
  arduboy.drawFastVLine(64 + lh, 7, 57, BLACK);
  arduboy.drawFastVLine(96 + lh, 7, 57, BLACK);

  player.Draw();
  for (int i = 0; i < ENEMIES_SIZE; i++)
    enemies[i].Draw();

  if (gameover) {
    arduboy.fillRect(38, 26, 51, 12, WHITE);
    arduboy.setCursor(40, 28);
    arduboy.print("GAMEOVER");
    arduboy.drawRect(38, 26, 51, 12, BLACK);
  }

  arduboy.display();
  if (options.screencasting && (arduboy.frameCount % 4) == 0)
    Serial.write(arduboy.getBuffer(), 1024);
}
