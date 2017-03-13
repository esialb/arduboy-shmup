/*
 * ShmupOptions.h
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPOPTIONS_H_
#define SRC_SHMUPOPTIONS_H_

#include <Arduboy.h>

class ShmupOptions {
public:
	int fps = 60;
	bool screencasting = false;
	bool mute = false;

	void selectOptions(Arduboy &arduboy);
	void selectFPS(Arduboy &arduboy);
	void selectMute(Arduboy &arduboy);

private:
	int menu(Arduboy &arduboy, const char *str, int length, int opt, bool (*handler)(ShmupOptions *options, Arduboy &arduboy, int opt));
};

#endif /* SRC_SHMUPOPTIONS_H_ */
