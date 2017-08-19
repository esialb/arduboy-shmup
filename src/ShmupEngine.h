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
#include "Constants.h"

#include "Player.h"
#include "Enemy.h"

class ShmupEngine {
public:
	int hp = INITIAL_HP;
	int score = 0;
	bool gameover = false;

	void tick();
	void draw();

private:
	int8_t skip_spawn = 0;
	int8_t skip_fire = 0;
	bool inverting = false;
	int8_t beamf = 0;
	bool collide = false;

	void destroy_enemy_tunes();
	void destroy_bullet_tones();
	void collision_tunes();
	void beam_tunes();
	void gameover_tunes();
	void check_beam();
	void check_gameover();
	void pause();
};

#endif /* SRC_SHMUPENGINE_H_ */
