/*
 * Externs.h
 *
 *  Created on: Aug 18, 2017
 *      Author: robin
 */

#ifndef SRC_EXTERNS_H_
#define SRC_EXTERNS_H_

#include "Constants.h"
#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "ShmupOptions.h"
#include "Player.h"
#include "Enemy.h"
#include "ShmupEngine.h"


extern Arduboy2 arduboy;
extern ArduboyTones tones;
extern ShmupOptions options;
extern Player player;
extern Enemy enemies[ENEMIES_SIZE];

void intro();

#endif /* SRC_EXTERNS_H_ */
