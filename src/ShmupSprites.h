/*
 * ShmupSprites.h
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#ifndef SRC_SPRITES_H_
#define SRC_SPRITES_H_

#include <stdint.h>
#include <Arduboy2.h>

class ShmupSprites {
public:
	static const uint8_t PLAYER[];
	static const uint8_t PLAYER_MASK[];

	static const uint8_t ENEMY[];
	static const uint8_t ENEMY_MASK[];

	static const uint8_t BULLET[];
	static const uint8_t BULLET_MASK[];

	static const uint8_t BEAM_MASK[];

	static const uint8_t NUM_NEG[];
	static const uint8_t NUM_0[];
	static const uint8_t NUM_1[];
	static const uint8_t NUM_2[];
	static const uint8_t NUM_3[];
	static const uint8_t NUM_4[];
	static const uint8_t NUM_5[];
	static const uint8_t NUM_6[];
	static const uint8_t NUM_7[];
	static const uint8_t NUM_8[];
	static const uint8_t NUM_9[];

	static void drawInt(Arduboy2 &arduboy, int n, int x, int y);

	static void draw(Arduboy2 &arduboy, const uint8_t *sprite, const uint8_t *mask, int x, int y);
	static bool collides(int x1, int y1, const uint8_t *m1, int x2, int y2, const uint8_t *m2);
};

#endif /* SRC_SPRITES_H_ */
