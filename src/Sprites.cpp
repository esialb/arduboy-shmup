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

const uint8_t Sprites::BEAM_MASK[] PROGMEM = {
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
};

bool Sprites::invert = false;

void Sprites::draw(Arduboy &arduboy, const uint8_t *sprite, const uint8_t *mask, int x, int y) {
	if(mask)
		arduboy.drawBitmap(x, y, mask, 8, 8, invert ? BLACK : WHITE);
	if(sprite)
		arduboy.drawBitmap(x, y, sprite, 8, 8, invert ? WHITE : BLACK);
}

bool Sprites::collides(int x1, int y1, const uint8_t *m1, int x2, int y2, const uint8_t *m2) {
	if(x1 - x2 >= 8 || x2 - x1 >= 8 || y1 - y2 >= 8 || y2 - y1 >= 8)
		return false;
	int xoff = x2 - x1;
	int yoff = y2 - y1;

	for(int i = 0; i < 8 - abs(xoff); i++) {
		uint8_t b1, b2;
		b1 = pgm_read_byte(m1 + i + (xoff > 0 ? xoff : 0));
		b2 = pgm_read_byte(m2 + i + (xoff < 0 ? -xoff : 0));
		if(yoff > 0)
			b2 = b2 << yoff;
		if(yoff < 0)
			b1 = b1 << -yoff;
		if(b1 & b2)
			return true;
	}

	return false;
}
