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
const int enemies_size = 4;
Enemy enemies[enemies_size];

int skip_spawn = 0;
int skip_fire = 0;

int score = 0;

bool inverting = false;

bool gameover = false;

int beamy;
int beamf = 0;

void setup() {
	arduboy.beginNoLogo();
	arduboy.fillScreen(BLACK);
	arduboy.display();

	arduboy.setFrameRate(60);
	Sprites::invert = false;
}

void update_bullet(Bullet *b) {
	if(arduboy.frameCount % b->fm == 0) {
		b->x += b->dx;
		b->y += b->dy;
	}
	if(b->x <= -8 || b->x >= 128 || b->y <= -8 || b->y >= 64)
		b->active = false;
}

void loop() {
	if(!arduboy.nextFrame())
		return;
	bool collide = false;

	if(gameover) {
		if(arduboy.pressed(B_BUTTON)) {
			while(arduboy.pressed(B_BUTTON))
				;
			gameover = false;
			player.x = 0;
			player.y = 28;
			player.active = true;
			for(int i = 0; i < player.bullets_size; i++)
				player.bullets[i].active = false;
			for(int i = 0; i < enemies_size; i++) {
				enemies[i].x = 0;
				enemies[i].y = 28;
				enemies[i].active = false;
				for(int j = 0; j < enemies[i].bullets_size; j++)
					enemies[i].bullets[j].active = false;
			}
			score = 0;
		}

		goto draw;
	}

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
			if(b->active) {
				for(int j = 0; j < enemies_size; j++) {
					Enemy *e = enemies + j;
					if(e->active && Sprites::collides(b->x, b->y, b->mask, e->x, e->y, e->mask)) {
						e->active = false;
						b->active = false;
						score += 10;
						break;
					}
					bool nb = true;
					for(int k = 0; nb && k < e->bullets_size; k++) {
						Bullet *b2 = e->bullets + k;
						if(b2->active && Sprites::collides(b->x, b->y, b->mask, b2->x, b2->y, b2->mask)) {
							b2->active = false;
							b->active = false;
							score += 1;
							nb = false;
						}
					}
				}
			}
		}
	}
	if(arduboy.pressed(A_BUTTON)) {
		if(skip_fire == 0) {
			for(int i = 0; i < player.bullets_size; i++) {
				Bullet *b = player.bullets + i;
				if(b->active)
					continue;
				b->active = true;
				b->x = player.x + 8;
				b->y = player.y;
				break;
			}
			skip_fire = 5;
		} else
			skip_fire--;
	} else {
		skip_fire = 0;
	}

	for(int i = 0; i < enemies_size; i++) {
		Enemy *e = enemies + i;
		if(!e->active) {
			if(random(0,16) == 0) {
				if(skip_spawn == 0) {
					e->x = 120;
					e->y = random(0, 64 - 8);
					e->active = true;
					int ry = random(0,4);
					if(ry == 0)
						e->dy = -1;
					else if(ry == 1)
						e->dy = 1;
					else
						e->dy = 0;
					skip_spawn = 3 + random(0, 6);
				} else
					skip_spawn--;
			}
		}
		if(arduboy.frameCount % e->fm == 0) {
			e->x += e->dx;
			e->y += e->dy;
		}
		if(e->x <= -8 || e->x >= 128 || e->y <= -8 || e->y >= 64) {
			e->active = false;
		}
		for(size_t j = 0; j < e->bullets_size; j++) {
			update_bullet(e->bullets + j);
		}
		for(size_t j = 0; j < e->bullets_size; j++) {
			if(e->active && !e->bullets[j].active) {
				if(random(0, 60) != 0)
					continue;
				Bullet *b = e->bullets + j;
				b->active = true;
				b->x = e->x - 8;
				b->y = e->y;
				break;
			}
		}

		if(!collide && e->active)
			collide = Sprites::collides(player.x, player.y, player.mask, e->x, e->y, e->mask);
		if(!collide) {
			for(int j = 0; j < e->bullets_size; j++) {
				Bullet *b = e->bullets + j;
				if(!b->active)
					continue;
				collide = Sprites::collides(player.x, player.y, player.mask, b->x, b->y, b->mask);
				if(collide)
					break;
			}
		}
	}

	if(collide) {
		if(!inverting) {
			arduboy.invert(true);
			inverting = true;
			score -= 100;
		}
	} else {
		inverting = false;
		arduboy.invert(false);
	}

	if(arduboy.pressed(B_BUTTON)) {
		if(beamf == -1 && score >= 50) {
			score -= 50;
			beamf = 120;
			beamy = player.y;
		} else if(beamf > 0) {
			beamf--;
			for(int i = 0; i < enemies_size; i++) {
				if(enemies[i].x > player.x) {
					if(Sprites::collides(
							enemies[i].x, enemies[i].y, enemies[i].mask,
							enemies[i].x, beamy, Sprites::BEAM_MASK))
						enemies[i].active = false;
				}
				for(int j = 0; j < enemies[i].bullets_size; j++) {
					if(enemies[i].bullets[j].x > player.x) {
						if(Sprites::collides(
								enemies[i].bullets[j].x, enemies[i].bullets[j].y, enemies[i].bullets[j].mask,
								enemies[i].bullets[j].x, beamy, Sprites::BEAM_MASK))
							enemies[i].bullets[j].active = false;
					}
				}
			}
		}
	} else
		beamf = -1;



	if(score < 0)
		gameover = true;

	draw:

	arduboy.fillScreen(WHITE);

	if(beamf > 0) {
		arduboy.drawFastHLine(player.x + 8, player.y + 3, 128 - player.x - 8, BLACK);
		arduboy.drawFastHLine(player.x + 8, player.y + 4, 128 - player.x - 8, BLACK);
	}

	char buf[12];
	itoa(score, buf, 10);
	arduboy.setCursor(0, 0);
	arduboy.print(buf);

	int lh = 31 - ((arduboy.frameCount >> 3) & 0x1F);
	arduboy.drawFastVLine(lh, 0, 64, Sprites::invert ? WHITE : BLACK);
	arduboy.drawFastVLine(32 + lh, 0, 64, Sprites::invert ? WHITE : BLACK);
	arduboy.drawFastVLine(64 + lh, 0, 64, Sprites::invert ? WHITE : BLACK);
	arduboy.drawFastVLine(96 + lh, 0, 64, Sprites::invert ? WHITE : BLACK);

	player.draw(arduboy);
	for(int i = 0; i < enemies_size; i++)
		enemies[i].draw(arduboy);

	if(gameover) {
		arduboy.setCursor(40, 28);
		arduboy.print("GAMEOVER");
	}


	arduboy.display();
}

