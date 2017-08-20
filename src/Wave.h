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
  void Draw();
private:
  uint8_t x[WAVE_SIZE], y[WAVE_SIZE];
  bool active[WAVE_SIZE];
  uint8_t wait = 0;
  uint8_t age[WAVE_SIZE];
};

#endif /* SRC_WAVE_H_ */
