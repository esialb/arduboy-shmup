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
	static const unsigned char PLAYER[];
	static const unsigned char PLAYER_MASK[];

	static const unsigned char ENEMY[];
	static const unsigned char ENEMY_MASK[];

	static const unsigned char BULLET[];
	static const unsigned char BULLET_MASK[];

	static bool invert;

	static void draw(Arduboy &arduboy, const unsigned char *sprite, const unsigned char *mask, int x, int y);
	static bool collides(int x1, int y1, const unsigned char *m1, int x2, int y2, const unsigned char *m2);
};

#endif /* SRC_SPRITES_H_ */
