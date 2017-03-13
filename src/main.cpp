/*
 * main.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: robin
 */

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "ShmupSprites.h"
#include "Player.h"
#include "Enemy.h"

#include "ShmupOptions.h"
#include "ShmupEeprom.h"


#include <EEPROM.h>

#define DESTROY_ENEMY_SCORE 10
#define DESTROY_BULLET_SCORE 1
#define PLAYER_HIT_SCORE -100
#define BEAM_COST_SCORE -50

Arduboy2 arduboy;
ArduboyTones tones(arduboy.audio.enabled);

ShmupOptions options;

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
	ShmupSprites::invert = true;
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
	ShmupSprites::invert = false;
	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
	while(arduboy.buttonsState() == 0)
		;
	while(arduboy.buttonsState() != 0)
		;
}

void setup() {
	arduboy.begin();

	if(arduboy.pressed(DOWN_BUTTON)) {
		options.screencasting = true;
		Serial.begin(9600);
		while(arduboy.pressed(DOWN_BUTTON))
			;
	}

	arduboy.initRandomSeed();
	ShmupEeprom::initRandom();

	intro();

	options.selectOptions(arduboy);

	arduboy.fillScreen(BLACK);
	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
	ShmupSprites::invert = true;

	arduboy.invert(false);
}



void update_bullet(Bullet *b) {
	if(arduboy.frameCount % b->fm == 0) {
		b->x += b->dx;
		b->y += b->dy;
	}
	if(b->x <= -8 || b->x >= 128 || b->y <= -8 || b->y >= 64)
		b->active = false;
}

int curvy(int age) {
	age = age % 20;
	if(age < 5)
		return -age;
	if(age < 10)
		return -(10 - age);
	if(age < 15)
		return age - 10;
	return 20 - age;
}

int jumpy_up(int age) {
	return sqrt(age % 9) / 2;
}

int jumpy_down(int age) {
	return -sqrt(age % 9) / 2;
}

void destroy_enemy_tunes() {
	if(options.mute)
		return;
	tones.tone(4400, 50);
}

void destroy_bullet_tones() {
	if(options.mute)
			return;
	tones.tone(8800, 10);
}

void collision_tunes() {
	if(options.mute)
		return;
	static int freq = 1100;
	tones.tone(freq, 50);
	freq *= 2;
	if(freq > 10000)
		freq = 1100;
}

void beam_tunes() {
	if(options.mute)
		return;
	static int freq = 2200;
	tones.tone(freq, 50);
	freq = freq / 1.3;
	if(freq < 300)
		freq = 2200;
}

void gameover_tunes() {
	if(options.mute)
		return;
	tones.tone(440, 1000);
}

void check_beam() {
	if(arduboy.pressed(B_BUTTON)) {
		if(beamf == -1 && score >= 50) {
			score += BEAM_COST_SCORE;
			beamf = 20;
		} else if(beamf > 0) {
			beam_tunes();
			beamf--;
			for(int i = 0; i < enemies_size; i++) {
				if(enemies[i].active && enemies[i].x > player.x) {
					if(ShmupSprites::collides(
							enemies[i].x, enemies[i].y, enemies[i].mask,
							enemies[i].x, player.y, ShmupSprites::BEAM_MASK)) {
						enemies[i].active = false;
						score += DESTROY_ENEMY_SCORE;
					}
				}
				for(int j = 0; j < enemies[i].bullets_size; j++) {
					if(enemies[i].bullets[j].active && enemies[i].bullets[j].x > player.x) {
						if(ShmupSprites::collides(
								enemies[i].bullets[j].x, enemies[i].bullets[j].y, enemies[i].bullets[j].mask,
								enemies[i].bullets[j].x, player.y, ShmupSprites::BEAM_MASK)) {
							enemies[i].bullets[j].active = false;
							score += DESTROY_BULLET_SCORE;
						}
					}
				}
			}
		}
	} else
		beamf = -1;

}

void pause() {
	arduboy.fillRect(44, 26, 39, 12, BLACK);
	arduboy.setCursor(46, 28);
	arduboy.print("PAUSED");
	arduboy.drawRect(44, 26, 39, 12, WHITE);
	arduboy.invert(true);
	arduboy.display();
	while(arduboy.buttonsState())
		;
	while(!arduboy.pressed(A_BUTTON) || !arduboy.pressed(B_BUTTON))
		;
	while(arduboy.buttonsState())
		;
}

void loop() {
	if(!arduboy.nextFrame())
		return;
	bool collide = false;

	if(gameover) {
		if(arduboy.pressed(B_BUTTON)) {
			while(arduboy.pressed(B_BUTTON))
				;
			options.selectOptions(arduboy);
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
					if(e->active && ShmupSprites::collides(b->x, b->y, b->mask, e->x, e->y, e->mask)) {
						e->active = false;
						b->active = false;
						score += DESTROY_ENEMY_SCORE;
						destroy_enemy_tunes();
						break;
					}
					bool nb = true;
					for(int k = 0; nb && k < e->bullets_size; k++) {
						Bullet *b2 = e->bullets + k;
						if(b2->active && ShmupSprites::collides(b->x, b->y, b->mask, b2->x, b2->y, b2->mask)) {
							b2->active = false;
							b->active = false;
							score += DESTROY_BULLET_SCORE;
							destroy_bullet_tones();
							nb = false;
						}
					}
				}
			}
		}
	}
	if(arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON)) {
		pause();
	} else if(arduboy.pressed(A_BUTTON)) {
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
					e->age = 0;
					e->dy = 0;
					int ry = random(0,5);
					if(ry == 0)
						e->dyfn=jumpy_down;
					else if(ry == 1)
						e->dyfn = jumpy_up;
					else if(ry == 2)
						e->dyfn = curvy;

					skip_spawn = 3 + random(0, 6);
				} else
					skip_spawn--;
			}
		}
		if(arduboy.frameCount % e->fm == 0) {
			e->x += e->dx;
			e->y += e->dy;
			e->age++;
			if(e->dyfn)
				e->dy = e->dyfn(e->age);
		}
		if(e->x <= -8 || e->x >= 128 || e->y <= -8 || e->y >= 64) {
			e->active = false;
		}
		for(size_t j = 0; j < e->bullets_size; j++) {
			update_bullet(e->bullets + j);
		}
		for(size_t j = 0; j < e->bullets_size; j++) {
			if(e->active && !e->bullets[j].active) {
				if(random(0, 90) != 0)
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
			if(ShmupSprites::collides(player.x, player.y, player.mask, e->x, e->y, e->mask)) {
				collide = true;
//				e->active = false;
			}
		}
		for(int j = 0; j < e->bullets_size; j++) {
			Bullet *b = e->bullets + j;
			if(!b->active)
				continue;
			if(ShmupSprites::collides(player.x, player.y, player.mask, b->x, b->y, b->mask)) {
				collide = true;
//				b->active = false;
			}
		}
	}

	if(collide) {
		collision_tunes();
		if(!inverting) {
			arduboy.invert(true);
			inverting = true;
			score += PLAYER_HIT_SCORE;
		}
	} else {
		inverting = false;
		arduboy.invert(false);
	}


	check_beam();




	if(score < 0) {
		gameover_tunes();
		gameover = true;
	}

	if(beamf > 0)
		arduboy.setRGBled(0, 0, arduboy.frameCount & 1 ? 255 : 0);
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

	arduboy.fillScreen(BLACK);

	if(beamf > 0) {
		arduboy.drawFastHLine(player.x + 8, player.y + 3, 128 - player.x - 8, WHITE);
		arduboy.drawFastHLine(player.x + 8, player.y + 4, 128 - player.x - 8, WHITE);
	}

	char buf[12];
	itoa(score, buf, 10);
	arduboy.setCursor(0, 0);
	arduboy.print(buf);

	int lh = 31 - ((arduboy.frameCount >> 3) & 0x1F);
	arduboy.drawFastVLine(lh, 0, 64, ShmupSprites::invert ? WHITE : BLACK);
	arduboy.drawFastVLine(32 + lh, 0, 64, ShmupSprites::invert ? WHITE : BLACK);
	arduboy.drawFastVLine(64 + lh, 0, 64, ShmupSprites::invert ? WHITE : BLACK);
	arduboy.drawFastVLine(96 + lh, 0, 64, ShmupSprites::invert ? WHITE : BLACK);

	player.draw(arduboy);
	for(int i = 0; i < enemies_size; i++)
		enemies[i].draw(arduboy);

	if(gameover) {
		arduboy.fillRect(38, 26, 51, 12, BLACK);
		arduboy.setCursor(40, 28);
		arduboy.print("GAMEOVER");
		arduboy.drawRect(38, 26, 51, 12, WHITE);
	}


	arduboy.display();
	if(options.screencasting)
		Serial.write(arduboy.getBuffer(), 1024);
}

