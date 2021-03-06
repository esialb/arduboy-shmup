/*
 * ShmupOptions.h
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPOPTIONS_H_
#define SRC_SHMUPOPTIONS_H_

#include <Arduboy2.h>

class ShmupOptions {
public:
  int fps = 60;
  bool screencasting = false;
  bool mute = false;

  void SelectOptions();
  void SelectFps();
  void SelectMute();

private:
  int Menu(const char *str, int length, int opt, bool (*handler)(int opt));
};

#endif /* SRC_SHMUPOPTIONS_H_ */
