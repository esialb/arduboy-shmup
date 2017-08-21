/*
 * ShmupEeprom.h
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPEEPROM_H_
#define SRC_SHMUPEEPROM_H_

#include <Arduino.h>

class ShmupEeprom {
public:
  static void InitRandom();
  static int LoadFps();
  static void SetFps(int fps);
  static bool LoadMute();
  static void SetMute(bool mute);
  static uint32_t LoadHighScore();
  static void setHighScore(uint32_t score);
};

#endif /* SRC_SHMUPEEPROM_H_ */
