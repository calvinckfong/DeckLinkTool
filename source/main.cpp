/*
 * main.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#include "decklink.h"
#include <string.h>
#include <iostream>

int main(int argc, char** argv)
{
	uint32_t deviceId = -1;

	if (argc>2)
		deviceId = atoi(argv[2]);

	Decklink dl;
	if (!dl.Init())	return -1;

	if (argc==1)
		dl.ListDevices();
	else if (strcmp(argv[1], "-p")==0)
		dl.ListDeviceProfile(deviceId);
	else if (strcmp(argv[1], "-d")==0)
		dl.ListDeviceDisplayMode(deviceId);
	else if (strcmp(argv[1], "-c")==0)
		dl.ListDeviceConfig(deviceId);
	else if (strcmp(argv[1], "-s")==0)
		dl.ListDeviceStatus(deviceId);
	else
	{
		std::cerr << "Unknown command " << argv[1] << std::endl;
		return -1;
	}

	return 0;
}
