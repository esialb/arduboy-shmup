/*
 * ShmupOptions.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#include <Arduboy2.h>
#include <ShmupOptions.h>

#include "ShmupEeprom.h"

int index_to_fps(int index);

int ShmupOptions::menu(Arduboy2 &arduboy, const char *str, int length, int opt, bool (*handler)(ShmupOptions *options, Arduboy2 &arduboy, int opt)) {
	for(;;) {
		arduboy.fillScreen(BLACK);
		arduboy.invert(false);
		arduboy.setTextWrap(true);
		arduboy.setCursor(0, 0);
		arduboy.print(str);
		arduboy.setCursor(0, 16+8*opt);
		arduboy.print(">");
		arduboy.display();
		if(screencasting)
			Serial.write(arduboy.getBuffer(), 1024);
		while(arduboy.buttonsState() != 0)
			;
		while(arduboy.buttonsState() == 0)
			;
		if(arduboy.pressed(UP_BUTTON) && opt > 0)
			opt--;
		if(arduboy.pressed(DOWN_BUTTON) && opt < length - 1)
			opt++;
		if(arduboy.pressed(A_BUTTON)) {
			while(arduboy.buttonsState())
				;
			return -opt -1;
		}
		if(arduboy.pressed(B_BUTTON)) {
			while(arduboy.buttonsState())
				;
			if(handler(this, arduboy, opt))
				return opt;
		}
	}
}

bool options_handler(ShmupOptions *options, Arduboy2& arduboy, int opt) {
	switch(opt) {
	case 0:
		return true;
	case 1:
		options->selectFPS(arduboy);
		return false;
	case 2:
		options->selectMute(arduboy);
		return false;
	}
	return false;
}

void ShmupOptions::selectOptions(Arduboy2 &arduboy) {
	const char *str =
			"options              "
			"                     "
			" begin               "
			" select speed        "
			" mute audio          "
			;
	int opt = 0;
	while(opt = menu(arduboy, str, 3, opt, options_handler)) {
		if(opt < 0)
			opt = -opt - 1;
	}

	ShmupEeprom::commit();

	arduboy.setFrameRate(index_to_fps(ShmupEeprom::loadFPS()));
	this->mute = ShmupEeprom::loadMute();
	if(this->mute)
		arduboy.audio.off();
	else
		arduboy.audio.on();
}

int index_to_fps(int index) {
	switch(index) {
	case 0: return 15;
	case 1: return 30;
	case 2: return 45;
	case 3: return 60;
	case 4: return 90;
	case 5: return 120;
	}
	return 60;
}

bool fps_handler(ShmupOptions *options, Arduboy2 &arduboy, int opt) {
	ShmupEeprom::setFPS(opt);
	return true;
}

void ShmupOptions::selectFPS(Arduboy2 &arduboy) {
	const char *str =
			"select speed         "
			"                     "
			" slow                "
			" easy                "
			" leisurely           "
			" normal              "
			" fast                "
			" insane              "
			;

	int opt = ShmupEeprom::loadFPS();
	if(opt < 0 || opt > 5)
		opt = 3;
	menu(arduboy, str, 6, opt, fps_handler);

}

bool mute_handler(ShmupOptions *options, Arduboy2 &arduboy, int opt) {
	ShmupEeprom::setMute(opt);
	return true;
}

void ShmupOptions::selectMute(Arduboy2 &arduboy) {
	const char *str =
			"select sounds        "
			"                     "
			" sound on            "
			" sound off           "
			;
	int opt = ShmupEeprom::loadMute();
	if(opt < 0 || opt > 1)
		opt = 0;
	menu(arduboy, str, 2, opt, mute_handler);
}
