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
		0b00011000,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00011000,
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
		0b00011000,
		0b00111100,
		0b00111100,
		0b00111100,
		0b01111110,
		0b11111111,
		0b11111111,
		0b00011000,
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
		0b00011000,
		0b00111100,
		0b00111100,
		0b00011000,
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
	uint8_t buf1[8], buf2[8];
	if(x1 - x2 >= 8 || x2 - x1 >= 8 || y1 - y2 >= 8 || y2 - y1 >= 8)
		return false;
	memcpy_P(buf1, m1, 8);
	int xoff = x2 - x1;
	int yoff = y2 - y1;
	memset(buf2, 0, 8);
	if(xoff == 0)
		memcpy_P(buf2, m2, 8);
	else if(xoff > 0) {
		memcpy_P(buf2 + xoff, m2, 8 - xoff);
	} else {
		memcpy_P(buf2, m2 + -xoff, 8 - -xoff);
	}
	if(yoff > 0) {
		for(int i = 0; i < 8; i++)
			buf2[i] = buf2[i] << yoff;
	} else if(yoff < 0) {
		for(int i = 0; i < 8; i++)
			buf1[i] = buf1[i] << -yoff;
	}
	for(int i = 0; i < 8; i++) {
		if(buf1[i] & buf2[i])
			return true;
	}
	return false;
}
