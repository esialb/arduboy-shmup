/*
 * Sprites.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Sprites.h>
#include <avr/pgmspace.h>

const uint8_t Sprites::PLAYER[] PROGMEM = {
		0b00011000,
		0b11100111,
		0b10000001,
		0b01000010,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000,
};

const uint8_t Sprites::PLAYER_MASK[] PROGMEM = {
		0b00000000,
		0b00011000,
		0b01111110,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00000000,
};

const uint8_t Sprites::ENEMY[] PROGMEM = {
		0b00011000,
		0b00100100,
		0b00100100,
		0b00100100,
		0b01000010,
		0b10000001,
		0b11100111,
		0b00011000,
};

const uint8_t Sprites::ENEMY_MASK[] PROGMEM = {
		0b00000000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00111100,
		0b01111110,
		0b00011000,
		0b00000000,
};

const uint8_t Sprites::BULLET[] PROGMEM = {
		0b00000000,
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00000000,
		0b00000000,
};

const uint8_t Sprites::BULLET_MASK[] PROGMEM = {
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
		0b00000000,
};

bool Sprites::invert = false;

void Sprites::draw(Arduboy &arduboy, const uint8_t *sprite, const uint8_t *mask, int x, int y) {
	if(mask)
		arduboy.drawBitmap(x, y, mask, 8, 8, invert ? BLACK : WHITE);
	if(sprite)
		arduboy.drawBitmap(x, y, sprite, 8, 8, invert ? WHITE : BLACK);
}

bool Sprites::collides(int x1, int y1, const uint8_t *m1, int x2, int y2, const uint8_t *m2) {
	if(abs(x1-x2) >= 8  || abs(y1 - y2) >= 8)
		return false;
	int o1 = 0, o2 = 0;
	if(x1 > x2)
		o2 = (x1 - x2);
	if(x1 < x2)
		o1 = (x2 - x1);
	for(int i = 0; i < 8 - abs(x1 - x2); i++) {
		uint8_t c1 = m1[i + o1];
		uint8_t c2 = m2[i + o2];
		if(y1 > y2)
			c1 <<= y1 - y2;
		if(y1 < y2)
			c2 <<= y2 - y1;
		if((c1 & c2) != 0)
			return true;
	}
	return false;
}
