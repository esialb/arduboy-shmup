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
  int score = 0;
  bool gameover = false;

  uint8_t weapon = 1;
  Beam beam;
  Wave wave;

  void Tick();
  void Draw();

private:
  int8_t skip_spawn_ = 0;
  int8_t skip_fire_ = 0;
  bool inverting_ = false;
  bool collide_ = false;

  void DestroyEnemyTone();
  void DestroyBulletTone();
  void CollisionTone();
  void BeamTone();
  void GameOverTone();
  void BeamCheck();
  void GameOverCheck();
  void CollideCheck();
  void DestroyCheck();
  void PlayerUpdate();
  void EnemiesUpdate();
  void MenuCheck();
  void WeaponCheck();
  void WeaponFire();
  void WeaponTick();
  void WeaponDraw();
};

#endif /* SRC_SHMUPENGINE_H_ */
