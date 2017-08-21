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
  static int hp;
  static uint32_t score;
  static bool gameover;
  static uint8_t level;
  static  uint32_t next_level_score;

  static void Tick();
  static void Draw();

  static uint8_t weapon_skip_fire;

  static int8_t skip_spawn;
  static int8_t skip_fire;
  static bool inverting;
  static bool collide;

  static void CollisionTone();
  static void BeamTone();
  static void GameOverTone();
  static void BeamCheck();
  static void GameOverCheck();
  static void CollideCheck();
  static void EnemiesUpdate();
  static void MenuCheck();
  static void WeaponCheck();
};

#endif /* SRC_SHMUPENGINE_H_ */
