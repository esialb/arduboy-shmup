/*
 * Beam.h
 *
 *  Created on: Aug 19, 2017
 *      Author: robin
 */

#ifndef SRC_BEAM_H_
#define SRC_BEAM_H_

#include <Arduino.h>

class Beam {
public:
  void Fire();
  void Tick();
  void Draw();
private:
  void BeamTone();

  int8_t beamf = -1;
};

#endif /* SRC_BEAM_H_ */
