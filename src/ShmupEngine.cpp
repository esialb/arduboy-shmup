/*
 * ShmupEngine.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: robin
 */

#include <ShmupEngine.h>

#include "ShmupSprites.h"

#include "Constants.h"

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

void ShmupEngine::DestroyEnemyTone() {
  if (options_.mute_)
    return;
  tones_.tone(800, 50);
}

void ShmupEngine::DestroyBulletTone() {
  if (options_.mute_)
    return;
  tones_.tone(8800, 10);
}

void ShmupEngine::CollisionTone() {
  if (options_.mute_)
    return;
  static int freq = 1100;
  tones_.tone(freq, 50);
  freq *= 2;
  if (freq > 10000)
    freq = 1100;
}

void ShmupEngine::BeamTone() {
  if (options_.mute_)
    return;
  static int freq = 2200;
  tones_.tone(freq, 50);
  freq = freq / 1.3;
  if (freq < 300)
    freq = 2200;
}

void ShmupEngine::GameOverTone() {
  if (options_.mute_)
    return;
  tones_.tone(440, 1000);
}

void ShmupEngine::WeaponCheck() {
  if (arduboy_.pressed(A_BUTTON))
    WeaponFire();
  else
    WeaponClear();
}

void ShmupEngine::WeaponFire() {
  if (beamf_ == -1 && hp_ >= 50) {
    hp_ += BEAM_COST_SCORE;
    beamf_ = 20;
  } else if (beamf_ > 0) {
    BeamTone();
    beamf_--;
    for (int i = 0; i < ENEMIES_SIZE; i++) {
      if (enemies_[i].active_ && enemies_[i].x_ > player_.x_) {
        if (ShmupSprites::Collides(
            enemies_[i].x_, enemies_[i].y_, ShmupSprites::ENEMY_MASK,
            enemies_[i].x_, player_.y_, ShmupSprites::BEAM_MASK)) {
          enemies_[i].active_ = false;
          hp_ += DESTROY_ENEMY_SCORE;
        }
      }
      for (uint8_t j = 0; j < enemies_[i].BULLETS_SIZE; j++) {
        if (enemies_[i].bullets_[j].active_
            && enemies_[i].bullets_[j].x_ > player_.x_) {
          if (ShmupSprites::Collides(
              enemies_[i].bullets_[j].x_, enemies_[i].bullets_[j].y_, ShmupSprites::BULLET_MASK,
              enemies_[i].bullets_[j].x_, player_.y_, ShmupSprites::BEAM_MASK)) {
            enemies_[i].bullets_[j].active_ = false;
            hp_ += DESTROY_BULLET_SCORE;
          }
        }
      }
    }
  }
}

void ShmupEngine::WeaponClear() {
  beamf_ = -1;
}

void ShmupEngine::PauseCheck() {
  if (!arduboy_.pressed(B_BUTTON))
    return;
  arduboy_.fillRect(44, 26, 39, 12, WHITE);
  arduboy_.setCursor(46, 28);
  arduboy_.print("PAUSED");
  arduboy_.drawRect(44, 26, 39, 12, BLACK);
  arduboy_.display();
  while (arduboy_.pressed(B_BUTTON))
    ;
  while (!arduboy_.pressed(B_BUTTON))
    ;
  while (arduboy_.pressed(B_BUTTON))
    ;
}

void ShmupEngine::GameOverCheck() {
  if (arduboy_.pressed(B_BUTTON)) {
    while (arduboy_.pressed(B_BUTTON))
      ;
    arduboy_.invert(false);
    options_.SelectOptions();
    gameover_ = false;
    player_.x_ = 0;
    player_.y_ = 28;
    player_.active_ = true;
    for (uint8_t i = 0; i < player_.BULLETS_SIZE; i++)
      player_.bullets_[i].active_ = false;
    for (uint8_t i = 0; i < ENEMIES_SIZE; i++) {
      enemies_[i].x_ = 0;
      enemies_[i].y_ = 28;
      enemies_[i].active_ = false;
      for (uint8_t j = 0; j < enemies_[i].BULLETS_SIZE; j++)
        enemies_[i].bullets_[j].active_ = false;
    }
    hp_ = 300;
    score_ = 0;
  }
}

void ShmupEngine::CollideCheck() {
  for (uint8_t i = 0; i < ENEMIES_SIZE; i++) {
    Enemy *e = enemies_ + i;
    if (e->active_) {
      if (ShmupSprites::Collides(player_.x_, player_.y_,
          ShmupSprites::PLAYER_MASK, e->x_, e->y_, ShmupSprites::ENEMY_MASK)) {
        collide_ = true;
      }
    }
    for (uint8_t j = 0; j < e->BULLETS_SIZE; j++) {
      Bullet *b = e->bullets_ + j;
      if (!b->active_)
        continue;
      if (ShmupSprites::Collides(player_.x_, player_.y_,
          ShmupSprites::PLAYER_MASK, b->x_, b->y_, ShmupSprites::BULLET_MASK)) {
        collide_ = true;
      }
    }
  }

  if (collide_) {
    CollisionTone();
    if (!inverting_) {
      arduboy_.invert(true);
      inverting_ = true;
      hp_ += PLAYER_HIT_SCORE;
    }
  } else {
    inverting_ = false;
    arduboy_.invert(false);
  }
}

void ShmupEngine::DestroyCheck() {
  for (uint8_t i = 0; i < player_.BULLETS_SIZE; i++) {
    if (player_.bullets_[i].active_) {
      Bullet *b = player_.bullets_ + i;
      if (b->active_) {
        for (int j = 0; j < ENEMIES_SIZE; j++) {
          Enemy *e = enemies_ + j;
          if (e->active_
              && ShmupSprites::Collides(b->x_, b->y_, ShmupSprites::BULLET_MASK,
                  e->x_, e->y_, ShmupSprites::ENEMY_MASK)) {
            e->active_ = false;
            b->active_ = false;
            hp_ += DESTROY_ENEMY_SCORE;
            score_ += DESTROY_ENEMY_SCORE;
            DestroyEnemyTone();
            break;
          }
          bool nb = true;
          for (uint8_t k = 0; nb && k < e->BULLETS_SIZE; k++) {
            Bullet *b2 = e->bullets_ + k;
            if (b2->active_
                && ShmupSprites::Collides(b->x_, b->y_,
                    ShmupSprites::BULLET_MASK, b2->x_, b2->y_,
                    ShmupSprites::BULLET_MASK)) {
              b2->active_ = false;
              b->active_ = false;
              hp_ += DESTROY_BULLET_SCORE;
              score_ += DESTROY_BULLET_SCORE;
              DestroyBulletTone();
              nb = false;
            }
          }
        }
      }
    }
  }
}

void ShmupEngine::PlayerUpdate() {
  if (player_.x_ > 0 && arduboy_.pressed(LEFT_BUTTON))
    player_.x_--;
  if (player_.x_ < WIDTH - 8 && arduboy_.pressed(RIGHT_BUTTON))
    player_.x_++;
  if (player_.y_ > 0 && arduboy_.pressed(UP_BUTTON))
    player_.y_--;
  if (player_.y_ < HEIGHT - 8 && arduboy_.pressed(DOWN_BUTTON))
    player_.y_++;

  for (uint8_t i = 0; i < player_.BULLETS_SIZE; i++) {
    if (player_.bullets_[i].active_) {
      Bullet *b = player_.bullets_ + i;
      b->Tick();
    }
  }
}

void ShmupEngine::EnemiesUpdate() {
  for (uint8_t i = 0; i < ENEMIES_SIZE; i++) {
    Enemy *e = enemies_ + i;
    if (!e->active_) {
      if (random(0, 16) == 0) {
        if (skip_spawn_ == 0) {
          e->x_ = 120;
          e->y_ = random(8, 64 - 16);
          e->active_ = true;
          e->fm_ = 2 + random(0, 3);
          e->dyfn_ = 0;
          e->age_ = 0;
          e->dy_ = 0;
          int ry = random(0, 5);
          if (ry == 0)
            e->dyfn_ = jumpy_down;
          else if (ry == 1)
            e->dyfn_ = jumpy_up;
          else if (ry == 2)
            e->dyfn_ = curvy;

          skip_spawn_ = 3 + random(0, 6);
        } else
          skip_spawn_--;
      }
    }
    if (arduboy_.frameCount % e->fm_ == 0) {
      e->x_ += e->dx_;
      e->y_ += e->dy_;
      e->age_++;
      if (e->dyfn_)
        e->dy_ = e->dyfn_(e->age_);
    }
    if (e->x_ <= -8 || e->x_ >= 128 || e->y_ <= -8 || e->y_ >= 64) {
      e->active_ = false;
    }
    for (size_t j = 0; j < e->BULLETS_SIZE; j++) {
      e->bullets_[j].Tick();
    }
    for (size_t j = 0; j < e->BULLETS_SIZE; j++) {
      if (e->active_ && !e->bullets_[j].active_) {
        if (random(0, 90) != 0)
          continue;
        Bullet *b = e->bullets_ + j;
        b->active_ = true;
        b->x_ = e->x_ - 8;
        b->y_ = e->y_;
        b->fm_ = e->fm_ - 1;
        break;
      }
    }
  }
}

void ShmupEngine::Tick() {
  if (!arduboy_.nextFrame())
    return;
  collide_ = false;

  if (gameover_) {
    GameOverCheck();
    return;
  }

  PlayerUpdate();

  DestroyCheck();
  WeaponCheck();

  PauseCheck();

  if (skip_fire_ == 0) {
    for (uint8_t i = 0; i < player_.BULLETS_SIZE; i++) {
      Bullet *b = player_.bullets_ + i;
      if (b->active_)
        continue;
      b->active_ = true;
      b->x_ = player_.x_ + 8;
      b->y_ = player_.y_;
      break;
    }
    skip_fire_ = 5;
  } else
    skip_fire_--;

  EnemiesUpdate();

  CollideCheck();

  if (hp_ < 0) {
    GameOverTone();
    gameover_ = true;
  }

  if (beamf_ > 0)
    arduboy_.setRGBled(0, 0, arduboy_.frameCount & 1 ? 255 : 0);
  else if (hp_ < 0)
    arduboy_.setRGBled(0, 0, 0);
  else if (hp_ < 100)
    arduboy_.setRGBled(255, 0, 0);
  else if (hp_ < 200)
    arduboy_.setRGBled(255, 255, 0);
  else
    arduboy_.setRGBled(0, 0, 0);
}

void ShmupEngine::Draw() {
  arduboy_.fillScreen(WHITE);

  if (beamf_ > 0) {
    arduboy_.drawFastHLine(player_.x_ + 8, player_.y_ + 3, 128 - player_.x_ - 8,
    BLACK);
    arduboy_.drawFastHLine(player_.x_ + 8, player_.y_ + 4, 128 - player_.x_ - 8,
    BLACK);
    int xoff = (4 + arduboy_.frameCount % 4 - player_.x_ % 4) % 4;
    int y = player_.y_ + 3;
    for (int x = player_.x_ + 8 + xoff; x < 128; x += 4)
      arduboy_.drawPixel(x, y, WHITE);
    y++;
    for (int x = player_.x_ + 8 + xoff + 1; x < 128; x += 4)
      arduboy_.drawPixel(x, y, WHITE);

  }

  arduboy_.drawFastHLine(0, 7, 128, BLACK);
  char buf[16];
  itoa(hp_ / 100, buf, 10);
  ShmupSprites::DrawInt(hp_ / 100, 128 - 4 * strlen(buf), 1);
  ShmupSprites::DrawInt(score_, 1, 1);

  //	char buf[12];
  //	itoa(score, buf, 10);
  //	arduboy.setCursor(0, 0);
  //	arduboy.print(buf);

  int lh = 31 - ((arduboy_.frameCount >> 3) & 0x1F);
  arduboy_.drawFastVLine(lh, 7, 57, BLACK);
  arduboy_.drawFastVLine(32 + lh, 7, 57, BLACK);
  arduboy_.drawFastVLine(64 + lh, 7, 57, BLACK);
  arduboy_.drawFastVLine(96 + lh, 7, 57, BLACK);

  player_.Draw();
  for (int i = 0; i < ENEMIES_SIZE; i++)
    enemies_[i].Draw();

  if (gameover_) {
    arduboy_.fillRect(38, 26, 51, 12, WHITE);
    arduboy_.setCursor(40, 28);
    arduboy_.print("GAMEOVER");
    arduboy_.drawRect(38, 26, 51, 12, BLACK);
  }

  arduboy_.display();
  if (options_.screencasting_ && (arduboy_.frameCount % 4) == 0)
    Serial.write(arduboy_.getBuffer(), 1024);
}
