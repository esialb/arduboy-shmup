/*
 * ShmupSprites.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <ShmupSprites.h>
#include <avr/pgmspace.h>

const uint8_t ShmupSprites::PLAYER[] PROGMEM = {
		0b00011000,
		0b11100111,
		0b10000001,
		0b01000010,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000,
};

const uint8_t ShmupSprites::PLAYER_MASK[] PROGMEM = {
		0b00011000,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00011000,
};

const uint8_t ShmupSprites::ENEMY[] PROGMEM = {
		0b00011000,
		0b00111100,
		0b10111101,
		0b10111101,
		0b11111111,
		0b11111111,
		0b11111111,
		0b00011000,
};

const uint8_t ShmupSprites::ENEMY_MASK[] PROGMEM = {
		0b00011000,
		0b00111100,
		0b10111101,
		0b10111101,
		0b11111111,
		0b11111111,
		0b11111111,
		0b00011000,
};

const uint8_t ShmupSprites::BULLET[] PROGMEM = {
		0b00000000,
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::BULLET_MASK[] PROGMEM = {
		0b00000000,
		0b00000000,
		0b00011000,
		0b00111100,
		0b00111100,
		0b00011000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::BEAM_MASK[] PROGMEM = {
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00111100,
};

const uint8_t ShmupSprites::NUM_NEG[] PROGMEM = {
		0b00100000,
		0b00100000,
		0b00100000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_0[] PROGMEM = {
		0b11111000,
		0b10001000,
		0b11111000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_1[] PROGMEM = {
		0b10010000,
		0b11111000,
		0b10000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_2[] PROGMEM = {
		0b11001000,
		0b10101000,
		0b10010000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_3[] PROGMEM = {
		0b10101000,
		0b10101000,
		0b11111000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_4[] PROGMEM = {
		0b00111000,
		0b00100000,
		0b11111000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_5[] PROGMEM = {
		0b10111000,
		0b10101000,
		0b01001000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_6[] PROGMEM = {
		0b11110000,
		0b10101000,
		0b11101000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_7[] PROGMEM = {
		0b10001000,
		0b01101000,
		0b00011000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_8[] PROGMEM = {
		0b11011000,
		0b10101000,
		0b11011000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

const uint8_t ShmupSprites::NUM_9[] PROGMEM = {
		0b10111000,
		0b10101000,
		0b01111000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
};

bool ShmupSprites::invert = false;

void ShmupSprites::drawInt(Arduboy2 &arduboy, int n, int x, int y) {
	char buf[16];
	itoa(n, buf, 10);
	y -= 3;
	for(char *c = buf; *c; c++) {
		uint8_t *sprite = NULL;
		switch(*c) {
		case '-': sprite = NUM_NEG; break;
		case '0': sprite = NUM_0; break;
		case '1': sprite = NUM_1; break;
		case '2': sprite = NUM_2; break;
		case '3': sprite = NUM_3; break;
		case '4': sprite = NUM_4; break;
		case '5': sprite = NUM_5; break;
		case '6': sprite = NUM_6; break;
		case '7': sprite = NUM_7; break;
		case '8': sprite = NUM_8; break;
		case '9': sprite = NUM_9; break;
		}
		draw(arduboy, sprite, NULL, x, y);
		x += 4;
	}
}

void ShmupSprites::draw(Arduboy2 &arduboy, const uint8_t *sprite, const uint8_t *mask, int x, int y) {
	if(mask)
		arduboy.drawBitmap(x, y, mask, 8, 8, invert ? BLACK : WHITE);
	if(sprite)
		arduboy.drawBitmap(x, y, sprite, 8, 8, invert ? WHITE : BLACK);
}

bool ShmupSprites::collides(int x1, int y1, const uint8_t *m1, int x2, int y2, const uint8_t *m2) {
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
