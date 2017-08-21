/*
 * ShmupEngine.h
 *
 *  Created on: Mar 12, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPENGINE_H_
#define SRC_SHMUPENGINE_H_

#include <Arduino.h>
#include "ShmupOptions.h"
#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Constants.h"

#include "Player.h"
#include "Enemy.h"
#include "Beam.h"
#include "Wave.h"

class ShmupEngine {
public:
  int hp = INITIAL_HP;
  uint32_t score = 0;
  bool gameover = false;
  uint8_t level = 0;
  uint32_t next_level_score = 0;

  void Tick();
  void Draw();

  uint8_t weapon_skip_fire = 0;

  int8_t skip_spawn = 0;
  int8_t skip_fire = 0;
  bool inverting = false;
  bool collide = false;

  void CollisionTone();
  void BeamTone();
  void GameOverTone();
  void BeamCheck();
  void GameOverCheck();
  void CollideCheck();
  void EnemiesUpdate();
  void MenuCheck();
  void WeaponCheck();
};

#endif /* SRC_SHMUPENGINE_H_ */
