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

Arduboy2 arduboy;
ArduboyTones tones(arduboy.audio.enabled);
ShmupOptions options;
Player player;
Enemy enemies[ENEMIES_SIZE];

ShmupEngine engine;

void intro() {
	arduboy.fillScreen(WHITE);
	arduboy.setCursor(37, 28);
	arduboy.setTextColor(BLACK);
	arduboy.setTextBackground(WHITE);
	arduboy.print("ArduSHMUP");
	Player player;
	player.x = 1;
	player.y = 28;
	player.active = true;
	player.draw();
	Enemy enemy;
	enemy.x = 119;
	enemy.active = true;
	for(int i = 0; i < 4; i++) {
		enemy.y = i * 16 + 4;
		enemy.draw();
	}
	enemy.x = 111;
	for(int i = 0; i < 3; i++) {
		enemy.y = i * 16 + 12;
		enemy.draw();
	}
	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
	while(arduboy.buttonsState() == 0)
		;
	while(arduboy.buttonsState() != 0)
		;
}

void setup() {
	arduboy.boot();
	arduboy.blank();
	arduboy.flashlight();
	arduboy.audio.begin();
	//	arduboy.bootLogo();

	if(arduboy.pressed(DOWN_BUTTON)) {
		options.screencasting = true;
		Serial.begin(9600);
		while(arduboy.pressed(DOWN_BUTTON))
			;
	}

	while(arduboy.buttonsState())
		;

	arduboy.initRandomSeed();
	ShmupEeprom::initRandom();

	intro();

	options.selectOptions();

	arduboy.fillScreen(BLACK);
	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
}



void loop() {
	engine.tick();
}
