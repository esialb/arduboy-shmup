/*
 * main.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Arduboy.h>
#include "Sprites.h"
#include "Player.h"
#include "Enemy.h"

Arduboy arduboy;

Player player;
const int enemies_size = 2;
Enemy enemies[enemies_size];

bool firing;

void setup() {
	arduboy.beginNoLogo();
	arduboy.fillScreen(WHITE);
	arduboy.display();

	arduboy.setFrameRate(60);
}

void update_bullet(Bullet *b) {
	b->x += b->dx;
	b->y += b->dy;
	if(b->x <= -8 || b->x >= 128 || b->y <= -8 || b->y >= 64)
		b->active = false;
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
			update_bullet(b);
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
	for(int i = 0; i < enemies_size; i++) {
		Enemy *e = enemies + i;
		if(!e->active) {
			if(random(0,63) < 62)
				continue;
			e->x = 120;
			e->y = random(0, 63);
			e->active = true;
		}
		e->x += e->dx;
		e->y += e->dy;
		if(e->x <= -8 || e->x >= 128 || e->y <= -8 || e->y >= 64) {
			e->active = false;
			for(size_t j = 0; j < e->bullets_size; j++)
				e->bullets[j].active = false;
		}
		else {
			for(size_t j = 0; j < e->bullets_size; j++) {
				update_bullet(e->bullets + j);
				if(!e->bullets[j].active) {
					if(random(0, 63) < 60)
						continue;
					Bullet *b = e->bullets + j;
					b->active = true;
					b->x = e->x - 8;
					b->y = e->y;
				}
			}
		}
	}

	arduboy.fillScreen(WHITE);

	int lh = 31 - ((arduboy.frameCount >> 3) & 0x1F);
	arduboy.drawFastVLine(lh, 0, 64, BLACK);
	arduboy.drawFastVLine(32 + lh, 0, 64, BLACK);
	arduboy.drawFastVLine(64 + lh, 0, 64, BLACK);
	arduboy.drawFastVLine(96 + lh, 0, 64, BLACK);

	player.draw(arduboy);
	for(int i = 0; i < enemies_size; i++)
		enemies[i].draw(arduboy);

	arduboy.display();
}

