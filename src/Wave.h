/*
 * Wave.h
 *
 *  Created on: Aug 19, 2017
 *      Author: robin
 */

#ifndef SRC_WAVE_H_
#define SRC_WAVE_H_

#include <Arduino.h>

#include "Constants.h"

class Wave {
public:
  void Fire();
  void Tick();
  void Collide();
  void Draw();

  int8_t dx = 1;
  int8_t x, y;
  bool active = false;
  uint8_t age;
};

#endif /* SRC_WAVE_H_ */
