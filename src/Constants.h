/*
 * Constants.h
 *
 *  Created on: Aug 6, 2017
 *      Author: robin
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "ShmupOptions.h"
#include "Player.h"
#include "Enemy.h"

#define ENEMIES_SIZE 8
#define INITIAL_HP 300
#define DESTROY_ENEMY_SCORE 10
#define DESTROY_BULLET_SCORE 1
#define PLAYER_HIT_SCORE -100
#define BEAM_COST_SCORE -50

extern Arduboy2 arduboy_;
extern ArduboyTones tones_;
extern ShmupOptions options_;
extern Player player_;
extern Enemy enemies_[ENEMIES_SIZE];

#endif /* SRC_CONSTANTS_H_ */
