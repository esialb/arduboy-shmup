/*
 * main.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Arduboy.h>
#include "Sprites.h"
#include "Player.h"
#include "Enemy.h"

#include "ShmupOptions.h"
#include "ShmupEeprom.h"
#include "ShmupEngine.h"

#include <EEPROM.h>

#define DESTROY_ENEMY_SCORE 10
#define DESTROY_BULLET_SCORE 1
#define PLAYER_HIT_SCORE -100
#define BEAM_COST_SCORE -50

Arduboy arduboy;

ShmupOptions options;

Player player;

ShmupEngine engine;

void intro() {
	arduboy.fillScreen(BLACK);
	arduboy.setCursor(37, 28);
	arduboy.print("ArduSHMUP");
	Player player;
	Sprites::invert = true;
	player.x = 0;
	player.y = 28;
	player.active = true;
	player.draw(arduboy);
	Enemy enemy;
	enemy.x = 120;
	enemy.active = true;
	for(int i = 0; i < 4; i++) {
		enemy.y = i * 16 + 4;
		enemy.draw(arduboy);
	}
	Sprites::invert = false;
	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
	while(arduboy.buttonsState() == 0)
		;
	while(arduboy.buttonsState() != 0)
		;
}

void setup() {
	arduboy.begin();

	if(arduboy.pressed(DOWN_BUTTON)) {
		options.screencasting = true;
		Serial.begin(9600);
		while(arduboy.pressed(DOWN_BUTTON))
			;
	}

	engine.arduboy = &arduboy;
	engine.options = &options;
	engine.player = &player;

	arduboy.initRandomSeed();
	ShmupEeprom::initRandom();

	intro();

	options.selectOptions(arduboy);

	arduboy.fillScreen(BLACK);
	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
	Sprites::invert = true;

	arduboy.invert(false);
}



void loop() {
	engine.tick();
}
