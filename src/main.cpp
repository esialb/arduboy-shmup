/*
 * main.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Arduboy.h>
#include "Sprites.h"
#include "Player.h"

Arduboy arduboy;

Player player;

bool firing;

void setup() {
	arduboy.beginNoLogo();
	arduboy.fillScreen(WHITE);
	arduboy.display();

	arduboy.setFrameRate(60);
}

void loop() {
	if(!arduboy.nextFrame())
		return;
	if(player.x > 0 && arduboy.pressed(LEFT_BUTTON))
		player.x--;
	if(player.x < WIDTH - 8 && arduboy.pressed(RIGHT_BUTTON))
		player.x++;
	if(player.y > 0 && arduboy.pressed(UP_BUTTON))
		player.y--;
	if(player.y < HEIGHT - 8 && arduboy.pressed(DOWN_BUTTON))
		player.y++;
	for(int i = 0; i < player.bullets_size; i++) {
		if(player.bullets[i].active) {
			Bullet *b = player.bullets + i;
			b->x += b->dx;
			b->y += b->dy;
			if(b->x <= -8 || b->x >= 128 || b->y <= -8 || b->y >= 64)
				b->active = false;
		}
	}
	if(arduboy.pressed(A_BUTTON)) {
		if(!firing) {
			for(int i = 0; i < player.bullets_size; i++) {
				Bullet *b = player.bullets + i;
				if(b->active)
					continue;
				b->active = true;
				b->x = player.x + 8;
				b->y = player.y;
				break;
			}
			firing = true;
		}
	} else {
		firing = false;
	}

	arduboy.fillScreen(WHITE);

	int lh = 31 - ((arduboy.frameCount >> 3) & 0x1F);
	arduboy.drawFastVLine(lh, 0, 64, BLACK);
	arduboy.drawFastVLine(32 + lh, 0, 64, BLACK);
	arduboy.drawFastVLine(64 + lh, 0, 64, BLACK);
	arduboy.drawFastVLine(96 + lh, 0, 64, BLACK);

	player.draw(arduboy);

	arduboy.display();
}

