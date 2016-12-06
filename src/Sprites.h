/*
 * Sprites.h
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#ifndef SRC_SPRITES_H_
#define SRC_SPRITES_H_

#include <stdint.h>
#include <Arduboy.h>

class Sprites {
public:
	static const uint8_t PLAYER[];
	static const uint8_t PLAYER_MASK[];

	static const uint8_t ENEMY[];
	static const uint8_t ENEMY_MASK[];

	static const uint8_t BULLET[];
	static const uint8_t BULLET_MASK[];

	static bool invert;

	static void draw(Arduboy &arduboy, const uint8_t *sprite, const uint8_t *mask, int x, int y);
	static bool collides(int x1, int y1, const uint8_t *m1, int x2, int y2, const uint8_t *m2);
};

#endif /* SRC_SPRITES_H_ */
