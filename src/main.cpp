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
const int enemies_size = 6;
Enemy enemies[enemies_size];

int skip_spawn = 0;
int skip_fire = 0;

int score = 300;

bool inverting = false;

bool gameover = false;

int beamf = 0;

void intro() {
	arduboy.fillScreen(BLACK);
	arduboy.setCursor(37, 28);
	arduboy.print("ArduSHMUP");
	Player player;
	Sprites::invert = true;
	player.x = 0;
	player.y = 28;
	player.active = true;
	player.draw(arduboy);
	Enemy enemy;
	enemy.x = 120;
	enemy.active = true;
	for(int i = 0; i < 4; i++) {
		enemy.y = i * 16 + 4;
		enemy.draw(arduboy);
	}
	Sprites::invert = false;
	arduboy.display();
	while(arduboy.buttonsState() == 0)
		;
	while(arduboy.buttonsState() != 0)
		;
}

void select_fps() {
	arduboy.fillScreen(BLACK);
	arduboy.invert(false);
	arduboy.setCursor(0, 0);
	arduboy.print("select framerate");
	arduboy.setCursor(6, 8);
	arduboy.print("15");
	arduboy.setCursor(6, 16);
	arduboy.print("30");
	arduboy.setCursor(6, 24);
	arduboy.print("45");
	arduboy.setCursor(6, 32);
	arduboy.print("60");
	arduboy.setCursor(6, 40);
	arduboy.print("90");
	arduboy.setCursor(6, 48);
	arduboy.print("120");

	int opt = 3;

	for(;;) {
		arduboy.setCursor(0, 8 * opt + 8);
		arduboy.print(">");
		arduboy.display();
		uint8_t button = 0;
		for(;;) {
			uint8_t bs = arduboy.buttonsState();
			while(arduboy.buttonsState() == bs)
				;
			if(arduboy.pressed(UP_BUTTON)) {
				button = UP_BUTTON;
				break;
			}
			if(arduboy.pressed(DOWN_BUTTON)) {
				button = DOWN_BUTTON;
				break;
			}
			if(arduboy.pressed(B_BUTTON)) {
				button = B_BUTTON;
				break;
			}
		}
		while(arduboy.pressed(button))
			;

		arduboy.setCursor(0, 8 * opt + 8);
		arduboy.print(" ");

		if(button == UP_BUTTON && opt > 0)
			opt--;
		if(button == DOWN_BUTTON && opt < 5)
			opt++;
		if(button == B_BUTTON)
			break;
	}
	switch(opt) {
	case 0:
		arduboy.setFrameRate(15);
		break;
	case 1:
		arduboy.setFrameRate(30);
		break;
	case 2:
		arduboy.setFrameRate(45);
		break;
	case 3:
		arduboy.setFrameRate(60);
		break;
	case 4:
		arduboy.setFrameRate(90);
		break;
	case 5:
		arduboy.setFrameRate(120);
		break;
	}
}

void setup() {
	arduboy.beginNoLogo();


	intro();

	select_fps();
	arduboy.fillScreen(BLACK);
	arduboy.display();
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

int curvy(int frames) {
	frames = frames % 20;
	if(frames < 5)
		return -frames;
	if(frames < 10)
		return -(10 - frames);
	if(frames < 15)
		return frames - 10;
	return 20 - frames;
}

void loop() {
	if(!arduboy.nextFrame())
		return;
	bool collide = false;

	if(gameover) {
		if(arduboy.pressed(B_BUTTON)) {
			while(arduboy.pressed(B_BUTTON))
				;
			select_fps();
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
			score = 300;
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
					e->fm = 2 + random(0, 3);
					e->dyfn = 0;
					int ry = random(0,4);
					if(ry == 0)
						e->dy = -1;
					else if(ry == 1)
						e->dy = 1;
					else if(ry == 2) {
						e->dy = 0;
						e->dyfn = curvy;
					} else
						e->dy = 0;
					skip_spawn = 3 + random(0, 6);
				} else
					skip_spawn--;
			}
		}
		if(arduboy.frameCount % e->fm == 0) {
			e->x += e->dx;
			e->y += e->dy;
			if(e->dyfn)
				e->dy = e->dyfn(arduboy.frameCount / e->fm);
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
				b->fm = e->fm - 1;
				break;
			}
		}

		if(e->active) {
			if(Sprites::collides(player.x, player.y, player.mask, e->x, e->y, e->mask)) {
				collide = true;
//				e->active = false;
			}
		}
		for(int j = 0; j < e->bullets_size; j++) {
			Bullet *b = e->bullets + j;
			if(!b->active)
				continue;
			if(Sprites::collides(player.x, player.y, player.mask, b->x, b->y, b->mask)) {
				collide = true;
//				b->active = false;
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
			beamf = 20;
		} else if(beamf > 0) {
			beamf--;
			for(int i = 0; i < enemies_size; i++) {
				if(enemies[i].x > player.x) {
					if(Sprites::collides(
							enemies[i].x, enemies[i].y, enemies[i].mask,
							enemies[i].x, player.y, Sprites::BEAM_MASK))
						enemies[i].active = false;
				}
				for(int j = 0; j < enemies[i].bullets_size; j++) {
					if(enemies[i].bullets[j].x > player.x) {
						if(Sprites::collides(
								enemies[i].bullets[j].x, enemies[i].bullets[j].y, enemies[i].bullets[j].mask,
								enemies[i].bullets[j].x, player.y, Sprites::BEAM_MASK))
							enemies[i].bullets[j].active = false;
					}
				}
			}
		}
	} else
		beamf = -1;



	if(score < 0)
		gameover = true;

	if(beamf > 0)
		arduboy.setRGBled(0, 0, 255);
	else if(score < 0)
		arduboy.setRGBled(0, 0, 0);
	else if(score < 50)
		arduboy.setRGBled(255, 0, 0);
	else if(score < 100)
		arduboy.setRGBled(255, 255, 0);
	else if(score < 150)
		arduboy.setRGBled(0, 255, 0);
	else
		arduboy.setRGBled(0, 255, 255);

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

