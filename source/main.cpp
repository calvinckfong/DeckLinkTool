/*
 * main.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#include "decklink.h"
#include <string.h>
#include <iostream>
#include <libgen.h>

void ShowHelp(char* argv)
{
	char *prog_name = basename(argv);
	printf("%s - A tool for Blackmagic DeckLink device\n", prog_name);
	printf("Usage: %s \n", prog_name);
	printf("\t List all detected DeckLink devices.\n\n");
	printf("Usage: %s [OPTION] [DeviceID]\n\n", prog_name);
	printf(" -p\tList the profile of the device.\n");
	printf(" -d\tList the display modes supported by the device.\n");
	printf(" -c\tList the configure of the device.\n");
	printf(" -s\tList the status of the device.\n");
	printf("\n");
	printf(" --capture\tCapture from the device.\n");
	printf(" --display\tDisplay onto the device.\n");
	printf("\n");
}

int main(int argc, char** argv)
{
	uint32_t deviceId = -1;

	if (argc>2)
		deviceId = atoi(argv[2]);

	Decklink dl;
	if (!dl.Init())	return -1;

	if (argc==1)
		dl.ListDevices();
	else if (strcmp(argv[1], "-h")==0)
		ShowHelp(argv[0]);
	else if (strcmp(argv[1], "-p")==0)
		dl.ListDeviceProfile(deviceId);
	else if (strcmp(argv[1], "-d")==0)
		dl.ListDeviceDisplayMode(deviceId);
	else if (strcmp(argv[1], "-c")==0)
		dl.ListDeviceConfig(deviceId);
	else if (strcmp(argv[1], "-s")==0)
		dl.ListDeviceStatus(deviceId);
	else if (strcmp(argv[1], "--capture")==0)
		dl.Capture(deviceId);
	else if (strcmp(argv[1], "--display")==0)
		dl.Display(deviceId);
	else
	{
		std::cerr << "Unknown command " << argv[1] << std::endl;
		return -1;
	}

	return 0;
}
