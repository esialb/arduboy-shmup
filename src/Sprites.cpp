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

bool Sprites::invert = false;

void Sprites::draw(Arduboy &arduboy, const unsigned char *sprite, const unsigned char *mask, int x, int y) {
	if(mask)
		arduboy.drawBitmap(x, y, mask, 8, 8, invert ? BLACK : WHITE);
	if(sprite)
		arduboy.drawBitmap(x, y, sprite, 8, 8, invert ? WHITE : BLACK);
}

bool Sprites::collides(int x1, int y1, const unsigned char *m1, int x2, int y2, const unsigned char *m2) {
	if(abs(x1-x2) >= 8  || abs(y1 - y2) >= 8)
		return false;
	const unsigned char *p1 = m1;
	const unsigned char *p2 = m2;
	if(y1 > y2)
		p2 += (y1 - y2);
	if(y1 < y2)
		p1 += (y2 - y1);
	while(p1 < m1 + 8 && p2 < m2 + 8) {
		unsigned char c1 = *p1;
		unsigned char c2 = *p2;
		if(x1 > x2)
			c1 = c1 >> (x1 - x2);
		if(x1 < x2)
			c1 = c1 << (x2 - x1);
		if(c1 & c2)
			return true;
		p1++;
		p2++;
	}
	return false;
}
