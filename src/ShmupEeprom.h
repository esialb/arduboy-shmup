/*
 * ShmupEeprom.h
 *
 *  Created on: Mar 11, 2017
 *      Author: robin
 */

#ifndef SRC_SHMUPEEPROM_H_
#define SRC_SHMUPEEPROM_H_

class ShmupEeprom {
public:
	static void init();
	static void commit();

	static void initRandom();
	static int loadFPS();
	static void setFPS(int fps);
	static bool loadMute();
	static void setMute(bool mute);
};

#endif /* SRC_SHMUPEEPROM_H_ */
