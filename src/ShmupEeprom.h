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
	static void Init();
	static void Commit();

	static void InitRandom();
	static int LoadFps();
	static void SetFps(int fps);
	static bool LoadMute();
	static void SetMute(bool mute);
};

#endif /* SRC_SHMUPEEPROM_H_ */
