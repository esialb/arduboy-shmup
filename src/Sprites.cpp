/*
 * Sprites.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Sprites.h>
#include <avr/pgmspace.h>

const unsigned char Sprites::PLAYER[] PROGMEM = {
		0b01100000,
		0b01010000,
		0b01011110,
		0b10000001,
		0b10000001,
		0b01011110,
		0b01010000,
		0b01100000,
};

const unsigned char Sprites::PLAYER_MASK[] PROGMEM = {
		0b01100000,
		0b01110000,
		0b01111110,
		0b11111111,
		0b11111111,
		0b01111110,
		0b01110000,
		0b01100000,
};

void Sprites::draw(Arduboy &arduboy, const unsigned char *sprite, const unsigned char *mask, int x, int y) {
	if(mask)
		arduboy.drawSlowXYBitmap(x, y, mask, 8, 8, WHITE);
	if(sprite)
		arduboy.drawSlowXYBitmap(x, y, sprite, 8, 8, BLACK);
}
