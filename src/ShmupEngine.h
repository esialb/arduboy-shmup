/*
 * ShmupEngine.h
 *
 *  Created on: Mar 12, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPENGINE_H_
#define SRC_SHMUPENGINE_H_

#include "ShmupOptions.h"
#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Player.h"
#include "Enemy.h"

#define INITIAL_SCORE 300

class ShmupEngine {
public:
	ShmupOptions *options;
	Arduboy2 *arduboy;
	ArduboyTones *tones;
	Player *player;
	static const int enemies_size = 4;
	Enemy enemies[enemies_size];
	int score = INITIAL_SCORE;
	bool gameover = false;

	void tick();

private:
	int skip_spawn = 0;
	int skip_fire = 0;
	bool inverting = false;
	int beamf = 0;

	void update_bullet(Bullet *b);
	void destroy_enemy_tunes();
	void destroy_bullet_tones();
	void collision_tunes();
	void beam_tunes();
	void gameover_tunes();
	void check_beam();
	void pause();
};

#endif /* SRC_SHMUPENGINE_H_ */
