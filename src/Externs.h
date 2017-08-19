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


extern Arduboy2 arduboy_;
extern ArduboyTones tones_;
extern ShmupOptions options_;
extern Player player_;
extern Enemy enemies_[ENEMIES_SIZE];



#endif /* SRC_EXTERNS_H_ */
