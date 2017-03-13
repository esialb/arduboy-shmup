/*
 * ShmupOptions.h
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPOPTIONS_H_
#define SRC_SHMUPOPTIONS_H_

class ShmupOptions {
public:
	int fps = 60;
	bool screencasting = false;
	bool mute = false;

	void selectOptions(Arduboy2 &arduboy);
	void selectFPS(Arduboy2 &arduboy);
	void selectMute(Arduboy2 &arduboy);

private:
	void menu(Arduboy2 &arduboy, const char *str, int length, int opt, bool (*handler)(ShmupOptions *options, Arduboy2 &arduboy, int opt));
};

#endif /* SRC_SHMUPOPTIONS_H_ */
