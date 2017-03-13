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

void ShmupEeprom::initRandom() {
	long int seed = random();
	seed += EEPROM.read(SEED_OFFSET);
	randomSeed(seed);
	EEPROM.write(SEED_OFFSET, random());
}

int ShmupEeprom::loadFPS() {
	return EEPROM.read(FPS_OFFSET);
}

void ShmupEeprom::setFPS(int fps) {
	EEPROM.write(FPS_OFFSET, fps);
}

bool ShmupEeprom::loadMute() {
	return EEPROM.read(MUTE_OFFSET);
}

void ShmupEeprom::setMute(bool mute) {
	EEPROM.write(MUTE_OFFSET, mute);
}
