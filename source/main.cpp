/*
 * main.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#include "decklink.h"

int main(int argc, char** argv)
{
	uint32_t deviceId = 0;
	if (argc>1)
		deviceId = atoi(argv[1]);

	Decklink dl;
	if (!dl.Init())	return -1;

	//dl.ListDevices();
	dl.ListDeviceProfile(deviceId);
	//dl.ListDeviceDisplayMode(deviceId);
	//dl.ListDeviceConfig(deviceId);

	return 0;
}
