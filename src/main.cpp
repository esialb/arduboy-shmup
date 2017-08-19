/*
 * main.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "ShmupSprites.h"
#include "Player.h"
#include "Enemy.h"

#include "ShmupOptions.h"
#include "ShmupEeprom.h"
#include "ShmupEngine.h"

#include "Constants.h"

#define DESTROY_ENEMY_SCORE 10
#define DESTROY_BULLET_SCORE 1
#define PLAYER_HIT_SCORE -100
#define BEAM_COST_SCORE -50

Arduboy2 arduboy_;
ArduboyTones tones_(arduboy_.audio.enabled);
ShmupOptions options_;
Player player_;
Enemy enemies_[ENEMIES_SIZE];

ShmupEngine engine;

void intro() {
  arduboy_.fillScreen(WHITE);
  arduboy_.setCursor(37, 28);
  arduboy_.setTextColor(BLACK);
  arduboy_.setTextBackground(WHITE);
  arduboy_.print("ArduSHMUP");
  Player player;
  player.x_ = 1;
  player.y_ = 28;
  player.active_ = true;
  player.Draw();
  Enemy enemy;
  enemy.x_ = 119;
  enemy.active_ = true;
  for (int i = 0; i < 4; i++) {
    enemy.y_ = i * 16 + 4;
    enemy.Draw();
  }
  enemy.x_ = 111;
  for (int i = 0; i < 3; i++) {
    enemy.y_ = i * 16 + 12;
    enemy.Draw();
  }
  arduboy_.display();
  if (options_.screencasting_)
    Serial.write(arduboy_.getBuffer(), 1024);
  while (arduboy_.buttonsState() == 0)
    ;
  while (arduboy_.buttonsState() != 0)
    ;
}

void setup() {
  arduboy_.boot();
  arduboy_.blank();
  arduboy_.flashlight();
  arduboy_.audio.begin();
  //	arduboy.bootLogo();

  if (arduboy_.pressed(DOWN_BUTTON)) {
    options_.screencasting_ = true;
    Serial.begin(9600);
    while (arduboy_.pressed(DOWN_BUTTON))
      ;
  }

  while (arduboy_.buttonsState())
    ;

  arduboy_.initRandomSeed();
  ShmupEeprom::InitRandom();

  intro();

  options_.SelectOptions();

  arduboy_.fillScreen(BLACK);
  arduboy_.display();
  if (options_.screencasting_)
    Serial.write(arduboy_.getBuffer(), 1024);
}

void loop() {
  engine.Tick();
  engine.Draw();
}
