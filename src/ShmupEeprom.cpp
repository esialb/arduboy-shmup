/*
 * ShmupEeprom.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#include <ShmupEeprom.h>

#include <Arduino.h>
#include <EEPROM.h>
#include <Arduboy2.h>

#define SEED_OFFSET (EEPROM_STORAGE_SPACE_START + 0)
#define FPS_OFFSET (EEPROM_STORAGE_SPACE_START + 1)
#define MUTE_OFFSET (EEPROM_STORAGE_SPACE_START + 2)
#define HIGH_SCORE_OFFSET (EEPROM_STORAGE_SPACE_START + 3)

void ShmupEeprom::InitRandom() {
  long int seed = random();
  seed += EEPROM.read(SEED_OFFSET);
  randomSeed(seed);
  EEPROM.write(SEED_OFFSET, random());
}

int ShmupEeprom::LoadFps() {
  return EEPROM.read(FPS_OFFSET);
}

void ShmupEeprom::SetFps(int fps) {
  EEPROM.write(FPS_OFFSET, fps);
}

bool ShmupEeprom::LoadMute() {
  return EEPROM.read(MUTE_OFFSET);
}

void ShmupEeprom::SetMute(bool mute) {
  EEPROM.write(MUTE_OFFSET, mute);
}

uint32_t ShmupEeprom::LoadHighScore() {
  uint32_t high_score = 0;
  int address = HIGH_SCORE_OFFSET;
  high_score |= EEPROM.read(address); address++;
  high_score <<= 8; high_score |= EEPROM.read(address); address++;
  high_score <<= 8; high_score |= EEPROM.read(address); address++;
  high_score <<= 8; high_score |= EEPROM.read(address);
  return high_score;
}

void ShmupEeprom::setHighScore(uint32_t high_score) {
  int address = HIGH_SCORE_OFFSET + 3;
  EEPROM.write(address, high_score); address--;
  high_score >>= 8; EEPROM.write(address, high_score); address--;
  high_score >>= 8; EEPROM.write(address, high_score); address--;
  high_score >>= 8; EEPROM.write(address, high_score);
}
