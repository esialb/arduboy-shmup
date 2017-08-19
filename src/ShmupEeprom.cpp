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

void ShmupEeprom::Init() {
	EEPROM.begin();
}

void ShmupEeprom::Commit() {
	EEPROM.end();
	EEPROM.begin();
}

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
	EEPROM.update(FPS_OFFSET, fps);
}

bool ShmupEeprom::LoadMute() {
	return EEPROM.read(MUTE_OFFSET);
}

void ShmupEeprom::SetMute(bool mute) {
	EEPROM.update(MUTE_OFFSET, mute);
}
