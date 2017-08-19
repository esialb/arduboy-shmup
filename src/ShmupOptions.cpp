/*
 * ShmupOptions.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#include <Arduboy2.h>
#include <ShmupOptions.h>

#include "ShmupEeprom.h"

#include "Constants.h"

int index_to_fps(int index);

int ShmupOptions::Menu(const char *str, int length, int opt, bool (*handler)(int opt)) {
	for(;;) {
		arduboy_.fillScreen(WHITE);
		arduboy_.setTextColor(BLACK);
		arduboy_.setTextBackground(WHITE);
		arduboy_.setTextWrap(true);
		arduboy_.setCursor(0, 0);
		arduboy_.print(str);
		arduboy_.setCursor(0, 16+8*opt);
		arduboy_.print(">");
		arduboy_.display();
		if(screencasting_)
			Serial.write(arduboy_.getBuffer(), 1024);
		while(arduboy_.buttonsState() != 0)
			;
		while(arduboy_.buttonsState() == 0)
			;
		if(arduboy_.pressed(UP_BUTTON) && opt > 0)
			opt--;
		if(arduboy_.pressed(DOWN_BUTTON) && opt < length - 1)
			opt++;
		if(arduboy_.pressed(A_BUTTON)) {
			while(arduboy_.buttonsState())
				;
			return -opt -1;
		}
		if(arduboy_.pressed(B_BUTTON)) {
			while(arduboy_.buttonsState())
				;
			if(handler(opt))
				return opt;
		}
	}
}

bool options_handler(int opt) {
	switch(opt) {
	case 0:
		return true;
	case 1:
		options_.SelectFps();
		return false;
	case 2:
		options_.SelectMute();
		return false;
	}
	return false;
}

void ShmupOptions::SelectOptions() {
	const char *str =
			"options              "
			"                     "
			" begin               "
			" select speed        "
			" mute audio          "
			;
	int opt = 0;
	while(opt = Menu(str, 3, opt, options_handler)) {
		if(opt < 0)
			opt = -opt - 1;
	}

	ShmupEeprom::Commit();

	arduboy_.setFrameRate(index_to_fps(ShmupEeprom::LoadFps()));
	this->mute_ = ShmupEeprom::LoadMute();
	if(this->mute_)
		arduboy_.audio.off();
	else
		arduboy_.audio.on();
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

bool fps_handler(int opt) {
	ShmupEeprom::SetFps(opt);
	return true;
}

void ShmupOptions::SelectFps() {
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

	int opt = ShmupEeprom::LoadFps();
	if(opt < 0 || opt > 5)
		opt = 3;
	Menu(str, 6, opt, fps_handler);

}

bool mute_handler(int opt) {
	ShmupEeprom::SetMute(opt);
	return true;
}

void ShmupOptions::SelectMute() {
	const char *str =
			"select sounds        "
			"                     "
			" sound on            "
			" sound off           "
			;
	int opt = ShmupEeprom::LoadMute();
	if(opt < 0 || opt > 1)
		opt = 0;
	Menu(str, 2, opt, mute_handler);
}
