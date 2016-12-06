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

	static void draw(Arduboy &arduboy, const unsigned char *sprite, const unsigned char *mask, int x, int y);
};

#endif /* SRC_SPRITES_H_ */
