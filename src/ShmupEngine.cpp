/*
 * ShmupEngine.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: robin
 */

#include <ShmupEngine.h>

#include "ShmupSprites.h"

#include "Constants.h"

#define DESTROY_ENEMY_SCORE 10
#define DESTROY_BULLET_SCORE 1
#define PLAYER_HIT_SCORE -100
#define BEAM_COST_SCORE -50



void ShmupEngine::update_bullet(Bullet *b) {
	if(arduboy.frameCount % b->fm == 0) {
		b->x += b->dx;
		b->y += b->dy;
	}
	if(b->x <= -8 || b->x >= 128 || b->y <= -8 || b->y >= 64)
		b->active = false;
}

int8_t curvy(int age) {
	age = age % 20;
	if(age < 5)
		return -age;
	if(age < 10)
		return -(10 - age);
	if(age < 15)
		return age - 10;
	return 20 - age;
}

int8_t jumpy_up(int age) {
	age = age % 12;
	if(age == 11)
		return 3;
	if(age == 10)
		return 2;
	if(age >= 6)
		return 1;
	if(age >= 4)
		return -1;
	return 0;
}

int8_t jumpy_down(int age) {
	return -jumpy_up(age);
}

void ShmupEngine::destroy_enemy_tunes() {
	if(options->mute)
		return;
	tones.tone(800, 50);
}

void ShmupEngine::destroy_bullet_tones() {
	if(options->mute)
			return;
	tones.tone(8800, 10);
}

void ShmupEngine::collision_tunes() {
	if(options->mute)
		return;
	static int freq = 1100;
	tones.tone(freq, 50);
	freq *= 2;
	if(freq > 10000)
		freq = 1100;
}

void ShmupEngine::beam_tunes() {
	if(options->mute)
		return;
	static int freq = 2200;
	tones.tone(freq, 50);
	freq = freq / 1.3;
	if(freq < 300)
		freq = 2200;
}

void ShmupEngine::gameover_tunes() {
	if(options->mute)
		return;
	tones.tone(440, 1000);
}

void ShmupEngine::check_beam() {
	if(arduboy.pressed(B_BUTTON)) {
		if(beamf == -1 && hp >= 50) {
			hp += BEAM_COST_SCORE;
			beamf = 20;
		} else if(beamf > 0) {
			beam_tunes();
			beamf--;
			for(int i = 0; i < enemies_size; i++) {
				if(enemies[i].active && enemies[i].x > player->x) {
					if(ShmupSprites::collides(
							enemies[i].x, enemies[i].y, ShmupSprites::ENEMY_MASK,
							enemies[i].x, player->y, ShmupSprites::BEAM_MASK)) {
						enemies[i].active = false;
						hp += DESTROY_ENEMY_SCORE;
					}
				}
				for(uint8_t j = 0; j < enemies[i].bullets_size; j++) {
					if(enemies[i].bullets[j].active && enemies[i].bullets[j].x > player->x) {
						if(ShmupSprites::collides(
								enemies[i].bullets[j].x, enemies[i].bullets[j].y, ShmupSprites::BULLET_MASK,
								enemies[i].bullets[j].x, player->y, ShmupSprites::BEAM_MASK)) {
							enemies[i].bullets[j].active = false;
							hp += DESTROY_BULLET_SCORE;
						}
					}
				}
			}
		}
	} else
		beamf = -1;

}

void ShmupEngine::pause() {
	arduboy.fillRect(44, 26, 39, 12, WHITE);
	arduboy.setCursor(46, 28);
	arduboy.print("PAUSED");
	arduboy.drawRect(44, 26, 39, 12, BLACK);
	arduboy.display();
	while(arduboy.buttonsState())
		;
	while(!arduboy.pressed(A_BUTTON) || !arduboy.pressed(B_BUTTON))
		;
	while(arduboy.buttonsState())
		;
}

void ShmupEngine::tick() {
	if(!arduboy.nextFrame())
		return;
	bool collide = false;

	if(gameover) {
		if(arduboy.pressed(B_BUTTON)) {
			while(arduboy.pressed(B_BUTTON))
				;
			options->selectOptions();
			gameover = false;
			player->x = 0;
			player->y = 28;
			player->active = true;
			for(uint8_t i = 0; i < player->bullets_size; i++)
				player->bullets[i].active = false;
			for(uint8_t i = 0; i < enemies_size; i++) {
				enemies[i].x = 0;
				enemies[i].y = 28;
				enemies[i].active = false;
				for(uint8_t j = 0; j < enemies[i].bullets_size; j++)
					enemies[i].bullets[j].active = false;
			}
			hp = 300;
			score = 0;
		}

		goto draw;
	}

	if(player->x > 0 && arduboy.pressed(LEFT_BUTTON))
		player->x--;
	if(player->x < WIDTH - 8 && arduboy.pressed(RIGHT_BUTTON))
		player->x++;
	if(player->y > 0 && arduboy.pressed(UP_BUTTON))
		player->y--;
	if(player->y < HEIGHT - 8 && arduboy.pressed(DOWN_BUTTON))
		player->y++;

	for(uint8_t i = 0; i < player->bullets_size; i++) {
		if(player->bullets[i].active) {
			Bullet *b = player->bullets + i;
			update_bullet(b);
			if(b->active) {
				for(int j = 0; j < enemies_size; j++) {
					Enemy *e = enemies + j;
					if(e->active && ShmupSprites::collides(b->x, b->y, ShmupSprites::BULLET_MASK, e->x, e->y, ShmupSprites::ENEMY_MASK)) {
						e->active = false;
						b->active = false;
						hp += DESTROY_ENEMY_SCORE;
						score += DESTROY_ENEMY_SCORE;
						destroy_enemy_tunes();
						break;
					}
					bool nb = true;
					for(uint8_t k = 0; nb && k < e->bullets_size; k++) {
						Bullet *b2 = e->bullets + k;
						if(b2->active && ShmupSprites::collides(b->x, b->y, ShmupSprites::BULLET_MASK, b2->x, b2->y, ShmupSprites::BULLET_MASK)) {
							b2->active = false;
							b->active = false;
							hp += DESTROY_BULLET_SCORE;
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
	} else if(!arduboy.pressed(A_BUTTON)) {
		if(skip_fire == 0) {
			for(uint8_t i = 0; i < player->bullets_size; i++) {
				Bullet *b = player->bullets + i;
				if(b->active)
					continue;
				b->active = true;
				b->x = player->x + 8;
				b->y = player->y;
				break;
			}
			skip_fire = 5;
		} else
			skip_fire--;
	} else {
		skip_fire = 0;
	}

	for(uint8_t i = 0; i < enemies_size; i++) {
		Enemy *e = enemies + i;
		if(!e->active) {
			if(random(0,16) == 0) {
				if(skip_spawn == 0) {
					e->x = 120;
					e->y = random(8, 64 - 16);
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
			if(ShmupSprites::collides(player->x, player->y, ShmupSprites::PLAYER_MASK, e->x, e->y, ShmupSprites::ENEMY_MASK)) {
				collide = true;
//				e->active = false;
			}
		}
		for(uint8_t j = 0; j < e->bullets_size; j++) {
			Bullet *b = e->bullets + j;
			if(!b->active)
				continue;
			if(ShmupSprites::collides(player->x, player->y, ShmupSprites::PLAYER_MASK, b->x, b->y, ShmupSprites::BULLET_MASK)) {
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
			hp += PLAYER_HIT_SCORE;
		}
	} else {
		inverting = false;
		arduboy.invert(false);
	}


	check_beam();




	if(hp < 0) {
		gameover_tunes();
		gameover = true;
	}

	if(beamf > 0)
		arduboy.setRGBled(0, 0, arduboy.frameCount & 1 ? 255 : 0);
	else if(hp < 0)
		arduboy.setRGBled(0, 0, 0);
	else if(hp < 50)
		arduboy.setRGBled(255, 0, 0);
	else if(hp < 100)
		arduboy.setRGBled(255, 255, 0);
	else if(hp < 150)
		arduboy.setRGBled(0, 255, 0);
	else
		arduboy.setRGBled(0, 0, 0);

	draw:

	arduboy.fillScreen(WHITE);

	if(beamf > 0) {
		arduboy.drawFastHLine(player->x + 8, player->y + 3, 128 - player->x - 8, BLACK);
		arduboy.drawFastHLine(player->x + 8, player->y + 4, 128 - player->x - 8, BLACK);
		int xoff = (4 + arduboy.frameCount % 4 - player->x % 4) % 4;
		int y = player->y + 3;
		for(int x = player->x + 8 + xoff; x < 128; x += 4)
					arduboy.drawPixel(x, y, WHITE);
		y++;
		for(int x = player->x + 8 + xoff + 1; x < 128; x += 4)
					arduboy.drawPixel(x, y, WHITE);

	}

	arduboy.drawFastHLine(0, 7, 128, BLACK);
	char buf[16];
	itoa(hp / 100, buf, 10);
	ShmupSprites::drawInt(hp / 100, 128 - 4 * strlen(buf), 1);
	ShmupSprites::drawInt(score, 1, 1);

//	char buf[12];
//	itoa(score, buf, 10);
//	arduboy.setCursor(0, 0);
//	arduboy.print(buf);

	int lh = 31 - ((arduboy.frameCount >> 3) & 0x1F);
	arduboy.drawFastVLine(lh, 7, 57, BLACK);
	arduboy.drawFastVLine(32 + lh, 7, 57, BLACK);
	arduboy.drawFastVLine(64 + lh, 7, 57, BLACK);
	arduboy.drawFastVLine(96 + lh, 7, 57, BLACK);

	player->draw();
	for(int i = 0; i < enemies_size; i++)
		enemies[i].draw();

	if(gameover) {
		arduboy.fillRect(38, 26, 51, 12, WHITE);
		arduboy.setCursor(40, 28);
		arduboy.print("GAMEOVER");
		arduboy.drawRect(38, 26, 51, 12, BLACK);
	}


	arduboy.display();
	if(options->screencasting && (arduboy.frameCount % 4) == 0)
		Serial.write(arduboy.getBuffer(), 1024);
}


