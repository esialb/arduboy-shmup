/*
 * main.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Arduboy.h>
#include "Sprites.h"

Arduboy arduboy;

int x, y;

void setup() {
	arduboy.beginNoLogo();
	arduboy.fillScreen(WHITE);
	arduboy.display();

	arduboy.setFrameRate(60);
}

void loop() {
	if(!arduboy.nextFrame())
		return;

	Sprites::draw(arduboy, NULL, Sprites::PLAYER_MASK, x, y);

	if(x > 0 && arduboy.pressed(LEFT_BUTTON))
		x--;
	if(x < WIDTH - 8 && arduboy.pressed(RIGHT_BUTTON))
		x++;
	if(y > 0 && arduboy.pressed(UP_BUTTON))
		y--;
	if(y < HEIGHT - 8 && arduboy.pressed(DOWN_BUTTON))
		y++;

	Sprites::draw(arduboy, Sprites::PLAYER, Sprites::PLAYER_MASK, x, y);
	arduboy.display();
}

