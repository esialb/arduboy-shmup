/*
 * Sprites.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Sprites.h>
#include <avr/pgmspace.h>

const unsigned char Sprites::PLAYER[] PROGMEM = {
		0b00011000,
		0b11100111,
		0b10000001,
		0b01000010,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000,
};

const unsigned char Sprites::PLAYER_MASK[] PROGMEM = {
		0b00011000,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00011000,
};

const unsigned char Sprites::ENEMY[] PROGMEM = {
		0b00011000,
		0b00100100,
		0b00100100,
		0b00100100,
		0b01000010,
		0b10000001,
		0b11100111,
		0b00011000,
};

const unsigned char Sprites::ENEMY_MASK[] PROGMEM = {
		0b00011000,
		0b00111100,
		0b00111100,
		0b00111100,
		0b01111110,
		0b11111111,
		0b11111111,
		0b00011000,
};

const unsigned char Sprites::BULLET[] PROGMEM = {
		0b00000000,
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00000000,
		0b00000000,
};

const unsigned char Sprites::BULLET_MASK[] PROGMEM = {
		0b00000000,
		0b00000000,
		0b00011000,
		0b00111100,
		0b00111100,
		0b00011000,
		0b00000000,
		0b00000000,
};

void Sprites::draw(Arduboy &arduboy, const unsigned char *sprite, const unsigned char *mask, int x, int y) {
	if(mask)
		arduboy.drawBitmap(x, y, mask, 8, 8, WHITE);
	if(sprite)
		arduboy.drawBitmap(x, y, sprite, 8, 8, BLACK);
}
