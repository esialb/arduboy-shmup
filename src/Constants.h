/*
 * Constants.h
 *
 *  Created on: Aug 6, 2017
 *      Author: robin
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

#define ENEMIES_SIZE 8

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "ShmupOptions.h"
#include "Player.h"
#include "Enemy.h"

extern Arduboy2 arduboy;
extern ArduboyTones tones;
extern ShmupOptions options;
extern Player player;
extern Enemy enemies[ENEMIES_SIZE];

#endif /* SRC_CONSTANTS_H_ */
