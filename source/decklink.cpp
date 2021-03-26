/*
 * decklink.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#include "decklink.h"
#include <iostream>
#include <map>

const char* BoonleanString[2] = {"FALSE", "TRUE"};

const char* VideoConnectionString[7] = {
		"Unspecified", 	"SDI", 	"HDMI", "Optical SDI",
		"Component", 	"Composite", 	"SVideo"
};

std::map<BMDDisplayMode, const char*> DisplayModeString =
{
	// SD Modes
	{bmdModeNTSC,     		"NTSC"		},
	{bmdModeNTSC2398, 		"NTSC 23.98Hz"},
	{bmdModePAL,				"PAL"			},
	{bmdModeNTSCp,				"NTSC-P"		},
	{bmdModePALp, 				"PAL-P"		},
	// HD 1080 Modes
	{bmdModeHD1080p2398,		"1080p 23.98Hz"},
	{bmdModeHD1080p24,		"1080p 24Hz"},
	{bmdModeHD1080p25,		"1080p 25Hz"},
	{bmdModeHD1080p2997,		"1080p 29.97Hz"},
	{bmdModeHD1080p30,		"1080p 30Hz"},
	{bmdModeHD1080p4795,		"1080p 47.95Hz"},
	{bmdModeHD1080p48,		"1080p 48Hz"},
	{bmdModeHD1080p50,		"1080p 50Hz"},
	{bmdModeHD1080p5994,		"1080p 59.94Hz"},
	{bmdModeHD1080p6000,		"1080p 60Hz"},
	{bmdModeHD1080p9590,		"1080p 95.90Hz"},
	{bmdModeHD1080p96,		"1080p 96Hz"},
	{bmdModeHD1080p100,		"1080p 100Hz"},
	{bmdModeHD1080p11988,	"1080p 119.88Hz"},
	{bmdModeHD1080p120,		"1080p 120Hz"},
	{bmdModeHD1080i50,		"1080i 50Hz"},
	{bmdModeHD1080i5994,		"1080i 59.94Hz"},
	{bmdModeHD1080i6000,		"1080i 60Hz"},
	// HD 720 Modes
	{bmdModeHD720p50,			"720p 50Hz"},
	{bmdModeHD720p5994,		"720p 59.94Hz"},
	{bmdModeHD720p60,			"720p 60Hz"},
	// 2K Modes
	{bmdMode2k2398,			"2K 23.98Hz"},
	{bmdMode2k24,				"2K 24Hz"},
	{bmdMode2k25,				"2K 25Hz"},
	// 2K DCI Modes
	{bmdMode2kDCI2398,		"2KDCI 23.98Hz"},
	{bmdMode2kDCI24,			"2KDCI 24Hz"},
	{bmdMode2kDCI25,			"2KDCI 25Hz"},
	{bmdMode2kDCI2997,		"2KDCI 29.97Hz"},
	{bmdMode2kDCI30,			"2KDCI 30Hz"},
	{bmdMode2kDCI4795,		"2KDCI 47.95Hz"},
	{bmdMode2kDCI48,			"2KDCI 28Hz"},
	{bmdMode2kDCI50,			"2KDCI 50Hz"},
	{bmdMode2kDCI5994,		"2KDCI 59.94Hz"},
	{bmdMode2kDCI60,			"2KDCI 60Hz"},
	{bmdMode2kDCI9590,		"2KDCI 95.90Hz"},
	{bmdMode2kDCI96,			"2KDCI 96Hz"},
	{bmdMode2kDCI100,			"2KDCI 100Hz"},
	{bmdMode2kDCI11988,		"2KDCI 119.88Hz"},
	{bmdMode2kDCI120,			"2KDCI 120Hz"},
	// 4K UHD Modes
	{bmdMode4K2160p2398,		"2160p 23.98Hz"},
	{bmdMode4K2160p24,		"2160p 24Hz"},
	{bmdMode4K2160p25,		"2160p 25Hz"},
	{bmdMode4K2160p2997,		"2160p 29.97Hz"},
	{bmdMode4K2160p30,		"2160p 30Hz"},
	{bmdMode4K2160p4795,		"2160p 47.95Hz"},
	{bmdMode4K2160p48,		"2160p 48Hz"},
	{bmdMode4K2160p50,		"2160p 50Hz"},
	{bmdMode4K2160p5994,		"2160p 59.94Hz"},
	{bmdMode4K2160p60,		"2160p 60Hz"},
	{bmdMode4K2160p9590,		"2160p 95.90Hz"},
	{bmdMode4K2160p96,		"2160p 96Hz"},
	{bmdMode4K2160p100,		"2160p 100Hz"},
	{bmdMode4K2160p11988,	"2160p 119.88Hz"},
	{bmdMode4K2160p120,		"2160p 120Hz"},
    // 4K DCI Modes
	{bmdMode4kDCI2398,		"4KDCI 23.98Hz"},
	{bmdMode4kDCI24,			"4KDCI 24Hz"},
	{bmdMode4kDCI25,			"4KDCI 25Hz"},
	{bmdMode4kDCI2997,		"4KDCI 29.97Hz"},
	{bmdMode4kDCI30,			"4KDCI 30Hz"},
	{bmdMode4kDCI4795,		"4KDCI 47.95Hz"},
	{bmdMode4kDCI48,			"4KDCI 48Hz"},
	{bmdMode4kDCI50,			"4KDCI 50Hz"},
	{bmdMode4kDCI5994,		"4KDCI 59.94Hz"},
	{bmdMode4kDCI60,			"4KDCI 60Hz"},
	{bmdMode4kDCI9590,		"4KDCI 95.90Hz"},
	{bmdMode4kDCI96,			"4KDCI 96Hz"},
	{bmdMode4kDCI100,			"4KDCI 100Hz"},
	{bmdMode4kDCI11988,		"4KDCI 119.88Hz"},
	{bmdMode4kDCI120,			"4KDCI 120Hz"},
    // 8K UHD Modes //
	{bmdMode8K4320p2398,		"4320p 23.98Hz"},
	{bmdMode8K4320p24,		"4320p 24Hz"},
	{bmdMode8K4320p25,		"4320p 25Hz"},
	{bmdMode8K4320p2997,		"4320p 29.97Hz"},
	{bmdMode8K4320p30,		"4320p 30Hz"},
	{bmdMode8K4320p4795,		"4320p 47.95Hz"},
	{bmdMode8K4320p48,		"4320p 48Hz"},
	{bmdMode8K4320p50,		"4320p 50Hz"},
	{bmdMode8K4320p5994,		"4320p 59.94Hz"},
	{bmdMode8K4320p60,		"4320p 60Hz"},
    // 8K DCI Modes
	{bmdMode8kDCI2398,		"8KDCI 23.98Hz"},
	{bmdMode8kDCI24,			"8KDCI 24Hz"},
	{bmdMode8kDCI25,			"8KDCI 25Hz"},
	{bmdMode8kDCI2997,		"8KDCI 29.97Hz"},
	{bmdMode8kDCI30,			"8KDCI 30Hz"},
	{bmdMode8kDCI4795,		"8KDCI 47.95Hz"},
	{bmdMode8kDCI48,			"8KDCI 48Hz"},
	{bmdMode8kDCI50,			"8KDCI 50Hz"},
	{bmdMode8kDCI5994,		"8KDCI 59.94Hz"},
	{bmdMode8kDCI60,			"8KDCI 60Hz"},
   // PC Modes
	{bmdMode640x480p60,		"640x480 60Hz"},
	{bmdMode800x600p60,		"800x600 60Hz"},
	{bmdMode1440x900p50,		"1440x900 50Hz"},
	{bmdMode1440x900p60,		"1440x900 60Hz"},
	{bmdMode1440x1080p50,	"1440x1080 50Hz"},
	{bmdMode1440x1080p60,	"1440x1080 60Hz"},
	{bmdMode1600x1200p50,	"1600x1200 50Hz"},
	{bmdMode1600x1200p60,	"1600x1200 60Hz"},
	{bmdMode1920x1200p50,	"1920x1200 50Hz"},
	{bmdMode1920x1200p60,	"1920x1280 60Hz"},
	{bmdMode1920x1440p50,	"1920x1440 50Hz"},
	{bmdMode1920x1440p60,	"1920x1440 60Hz"},
	{bmdMode2560x1440p50,	"2560x1440 50Hz"},
	{bmdMode2560x1440p60,	"2560x1440 60Hz"},
	{bmdMode2560x1600p50,	"2560x1600 50Hz"},
	{bmdMode2560x1600p60,	"2560x1600 60Hz"},
	// RAW Modes for Cintel (input only)
	{bmdModeCintelRAW,		"Cintel Raw"},
	{bmdModeCintelCompressedRAW,		"Cintel Compressed Raw"},
	// Special Modes
	{bmdModeUnknown,		"Unknown"},
};

std::map<BMDPixelFormat, const char*> PixelFormatString =
{
	{bmdFormatUnspecified,	"Unspecified"},
	{bmdFormat8BitYUV, 		"YUV 8-bit"},
	{bmdFormat10BitYUV, 		"YUV 10-bit"},
	{bmdFormat8BitARGB, 		"ARGB 8-bit"},
	{bmdFormat8BitBGRA, 		"BGRA 8-bit"},
	{bmdFormat10BitRGB, 		"RGB 10-bit"},
	{bmdFormat12BitRGB, 		"RGB 12-bit"},
	{bmdFormat12BitRGBLE,	"RGB 12-bit Little-endian"},
	{bmdFormat10BitRGBXLE, 	"RGB 10-bit Little-endian SMPTE levels"},
	{bmdFormat10BitRGBX, 	"RGB 10-bit Big-endian SMPTE levels"},
	{bmdFormatH265, 			"HEVC"},
	{bmdFormatDNxHR, 			"DNxHR"},
	{bmdFormat12BitRAWGRBG, "12-bit Raw data GRBG"},
	{bmdFormat12BitRAWJPEG, "12-bit Raw data JPEG"}
};

std::map<BMDPixelFormat, const char*> PanelTypeString =
{
	{bmdPanelNotDetected, 				""},
	{bmdPanelTeranexMiniSmartPanel,	""},
};

Decklink::Decklink() :
	m_deckLinkIterator(NULL)
{

}

Decklink::~Decklink()
{

}

bool Decklink::Init()
{
	m_deckLinkIterator = CreateDeckLinkIteratorInstance();
	if (m_deckLinkIterator == NULL)
	{
		std::cerr << "Decklink drivers may not be installed." << std::endl;
		return false;
	}

	// Query API version
	IDeckLinkAPIInformation *deckLinkAPIInformation = NULL;
	HRESULT result = m_deckLinkIterator->QueryInterface(IID_IDeckLinkAPIInformation, (void**)&deckLinkAPIInformation);
	if (result == S_OK)
	{
		int64_t      deckLinkVersion;
		int          dlVerMajor, dlVerMinor, dlVerPoint;

		deckLinkAPIInformation->GetInt(BMDDeckLinkAPIVersion, &deckLinkVersion);

		dlVerMajor = (deckLinkVersion & 0xFF000000) >> 24;
		dlVerMinor = (deckLinkVersion & 0x00FF0000) >> 16;
		dlVerPoint = (deckLinkVersion & 0x0000FF00) >> 8;

		std::cout << "DeckLink API version " << dlVerMajor << "." << dlVerMinor << "." << dlVerPoint << std::endl;
		deckLinkAPIInformation->Release();
	}

	int 			deviceCount=0;
	IDeckLink		*deckLink = NULL;
	while (m_deckLinkIterator->Next(&deckLink) == S_OK)
	{
		char *modelName;
		deckLink->GetModelName((const char**)&modelName);
		//std::cout << deviceCount << ": " << modelName << std::endl;
		m_deckLinkDeviceList.push_back(deckLink);
		m_deckLinkDeviceName.push_back(modelName);

		deviceCount++;
	}
	std::cout << deviceCount << " DeckLink devices found." << std::endl;
	std::cout << std::endl;

	return true;
}

void Decklink::ListDevices()
{
	std::cout << "====== Device List ======" << std::endl;
	for (size_t i=0; i<m_deckLinkDeviceList.size(); i++)
	{
		//char *modelName;
		//m_deckLinkDeviceList[i]->GetModelName((const char**)&modelName);
		//printf("% 2d\t%s\n", i, modelName);
		printf("%2d\t%s\n", i, m_deckLinkDeviceName[i]);
	}

	std::cout << std::endl;
}

void Decklink::ListDeviceProfile(uint32_t deviceId)
{
	HRESULT result;
	IDeckLinkProfileAttributes *deckLinkAttributes = NULL;

	if (deviceId<m_deckLinkDeviceList.size())
	{
		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkProfileAttributes, (void**)&deckLinkAttributes);
		if (result==S_OK)
		{
			int64_t inPorts, outPorts;
			int64_t videoIOSupport;
			int64_t duplex;
			bool supportHDRMetadata;
			bool supportColorspaceMetadata;

			std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceName[deviceId] << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkVideoInputConnections, &inPorts);
			printf(" %-30s: ", "Input Port");
			if (inPorts&bmdVideoConnectionSDI) 			std::cout << "[SDI] ";
			if (inPorts&bmdVideoConnectionHDMI)			std::cout << "[HDMI] ";
			if (inPorts&bmdVideoConnectionOpticalSDI) 	std::cout << "[Optical SDI] ";
			if (inPorts&bmdVideoConnectionComponent)	std::cout << "[Component] ";
			if (inPorts&bmdVideoConnectionComposite)	std::cout << "[Composite] ";
			if (inPorts&bmdVideoConnectionSVideo) 		std::cout << "[SVideo] ";
			std::cout << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkVideoOutputConnections, &outPorts);
			printf(" %-30s: ", "Output Port");
			if (outPorts&bmdVideoConnectionSDI) 		std::cout << "[SDI] ";
			if (outPorts&bmdVideoConnectionHDMI)		std::cout << "[HDMI] ";
			if (outPorts&bmdVideoConnectionOpticalSDI)	std::cout << "[Optical SDI] ";
			if (outPorts&bmdVideoConnectionComponent)	std::cout << "[Component] ";
			if (outPorts&bmdVideoConnectionComposite)	std::cout << "[Composite] ";
			if (outPorts&bmdVideoConnectionSVideo)		std::cout << "[SVideo] ";
			std::cout << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkVideoIOSupport, &videoIOSupport);
			printf(" %-30s: %s\n", "Capture",  BoonleanString[!!(videoIOSupport&bmdDeviceSupportsCapture)]);
			printf(" %-30s: %s\n", "Playback", BoonleanString[!!(videoIOSupport&bmdDeviceSupportsPlayback)]);

			deckLinkAttributes->GetInt(BMDDeckLinkDuplex, &duplex);
			printf(" %-30s: ", "Duplex");
			if (duplex == bmdDuplexFull) 			std::cout << "Full Duplex";
			else if (duplex == bmdDuplexHalf) 		std::cout << "Half Duplex";
			else if (duplex == bmdDuplexSimplex)	std::cout << "Simplex";
			else if (duplex == bmdDuplexInactive)	std::cout << "Inactive";
			std::cout << std::endl;

			deckLinkAttributes->GetFlag(BMDDeckLinkSupportsHDRMetadata, &supportHDRMetadata);
			printf(" %-30s: %s\n", "Support HDR Metadata", BoonleanString[supportHDRMetadata]);

			deckLinkAttributes->GetFlag(BMDDeckLinkSupportsColorspaceMetadata, &supportColorspaceMetadata);
			printf(" %-30s: %s\n", "Support Colorspace Metadata", BoonleanString[supportColorspaceMetadata]);

			std::cout << std::endl;
		}
	}
	else
	{
		std::cerr << "Invalid device Id " << deviceId << std::endl;
	}
}

void Decklink::ListDeviceDisplayMode(uint32_t deviceId)
{
	HRESULT result;
	IDeckLinkInput      *deckLinkInput = NULL;
	IDeckLinkOutput     *deckLinkOutput = NULL;
	IDeckLinkDisplayModeIterator	*displayModeIterator;
	IDeckLinkDisplayMode			*displayMode;

	if (deviceId<m_deckLinkDeviceList.size())
	{
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceName[deviceId] << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkInput, (void**)&deckLinkInput);
		if (result==S_OK)
		{
			int modeCount = 0;
			std::cout << "Input modes supported:" << std::endl;
			result = deckLinkInput->GetDisplayModeIterator(&displayModeIterator);
			while (displayModeIterator->Next(&displayMode) == S_OK)
			{
				char* modeName;
				BMDDisplayMode bMDdisplayMode;

				if (displayMode->GetName(const_cast<const char**>(&modeName)) != S_OK) continue;

				bMDdisplayMode = displayMode->GetDisplayMode();

				//std::cout << std::dec << modeCount << ": " << modeName << " (0x" << std::hex << bMDdisplayMode << ")" << std::endl;
				printf(" %2d: %-20s (0x%08x)\n", modeCount, modeName, bMDdisplayMode);

				modeCount++;
			}
		}

		std::cout << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkOutput, (void**)&deckLinkOutput);
		if (result==S_OK)
		{
			int modeCount = 0;
			std::cout << "Output modes supported:" << std::endl;
			result = deckLinkOutput->GetDisplayModeIterator(&displayModeIterator);
			while (displayModeIterator->Next(&displayMode) == S_OK)
			{
				char* modeName;
				BMDDisplayMode bMDdisplayMode;

				if (displayMode->GetName(const_cast<const char**>(&modeName)) != S_OK) continue;

				bMDdisplayMode = displayMode->GetDisplayMode();

				//std::cout << std::dec << modeCount << ": " << modeName << " (0x" << std::hex << bMDdisplayMode << ")" << std::endl;
				printf(" %2d: %-20s (0x%08x)\n", modeCount, modeName, bMDdisplayMode);

				modeCount++;
			}
		}

		std::cout << std::endl;
	}
	else
	{
		std::cerr << "Invalid device Id " << deviceId << std::endl;
	}
}

void Decklink::ListDeviceConfig(uint32_t deviceId)
{
	HRESULT result;
	IDeckLinkConfiguration      *deckLinkConfiguration = NULL;

	if (deviceId<m_deckLinkDeviceList.size())
	{
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceName[deviceId] << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkConfiguration, (void**)&deckLinkConfiguration);
		if (result==S_OK)
		{
			int64_t videoInputConnection;
			int64_t videoOutputConnection;

			deckLinkConfiguration->GetInt(bmdDeckLinkConfigVideoInputConnection, &videoInputConnection);
			std::cout << "Video input connection ";
			for (int i=0; i<6; i++)
			{
				if (videoInputConnection & (1<<i))
					std::cout << VideoConnectionString[i] << " ";
			}
			std::cout << std::endl << std::endl;

			std::cout << "Video output connection ";
			deckLinkConfiguration->GetInt(bmdDeckLinkConfigVideoOutputConnection, &videoOutputConnection);
			for (int i=0; i<6; i++)
			{
				if (videoOutputConnection & (1<<i))
					std::cout << VideoConnectionString[i] << " ";
			}
			std::cout << std::endl << std::endl;
		}
	}
	else
	{
		std::cerr << "Invalid device Id " << deviceId << std::endl;
	}
}

void Decklink::ListDeviceStatus(uint32_t deviceId)
{
	HRESULT result;
	IDeckLinkStatus* deckLinkStatus = NULL;

	if (deviceId<m_deckLinkDeviceList.size())
	{
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceName[deviceId] << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkStatus, (void**)&deckLinkStatus);
		if (result==S_OK)
		{
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusBusy);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusDetectedVideoInputMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusDetectedVideoInputFlags);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoInputMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoInputPixelFormat);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoInputFlags);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoOutputMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoOutputFlags);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusPCIExpressLinkWidth);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusPCIExpressLinkSpeed);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusLastVideoOutputPixelFormat);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReferenceSignalMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReferenceSignalFlags);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusInterchangeablePanelType);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusDeviceTemperature);
			std::cout << std::endl;
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusVideoInputSignalLocked);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReferenceSignalLocked);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReceivedEDID);
			std::cout << std::endl;
		}
	}
}

void Decklink::ShowStatus(IDeckLinkStatus* deckLinkStatus, BMDDeckLinkStatusID statusID)
{
	HRESULT	result;
	bool 		boolVal = false;
	int64_t	intVal = 0;

	switch (statusID) {
	case bmdDeckLinkStatusDetectedVideoInputMode:
	case bmdDeckLinkStatusDetectedVideoInputFlags:
	case bmdDeckLinkStatusCurrentVideoInputMode:
	case bmdDeckLinkStatusCurrentVideoInputPixelFormat:
	case bmdDeckLinkStatusCurrentVideoInputFlags:
	case bmdDeckLinkStatusCurrentVideoOutputMode:
	case bmdDeckLinkStatusCurrentVideoOutputFlags:
	case bmdDeckLinkStatusPCIExpressLinkWidth:
	case bmdDeckLinkStatusPCIExpressLinkSpeed:
	case bmdDeckLinkStatusLastVideoOutputPixelFormat:
	case bmdDeckLinkStatusReferenceSignalMode:
	case bmdDeckLinkStatusReferenceSignalFlags:
	case bmdDeckLinkStatusBusy:
	case bmdDeckLinkStatusInterchangeablePanelType:
	case bmdDeckLinkStatusDeviceTemperature:
		result = deckLinkStatus->GetInt(statusID, &intVal);
		break;

	case bmdDeckLinkStatusVideoInputSignalLocked:
	case bmdDeckLinkStatusReferenceSignalLocked:
	case bmdDeckLinkStatusReceivedEDID:
		result = deckLinkStatus->GetFlag(statusID, &boolVal);
		break;

	default:
		std::cerr << "Unknown status ID." << std::endl;
		return;
	}

	if (result == S_OK)
	{
		switch (statusID) {
		case bmdDeckLinkStatusDetectedVideoInputMode:
		{
			printf("%-40s: %s\n", "Detected Video Input Mode", DisplayModeString[intVal]);
			break;
		}
		case bmdDeckLinkStatusDetectedVideoInputFlags:
		{
			printf("%-40s: ", "Detected Video Input Flags");
			if (intVal & bmdDeckLinkVideoStatusPsF) std::cout << "[PsF]";
			if (intVal & bmdDeckLinkVideoStatusDualStream3D) std::cout << "[3D]";
			std::cout << std::endl;
			break;
		}
		case bmdDeckLinkStatusCurrentVideoInputMode:
		{
			printf("%-40s: %s\n", "Current Video Input Mode", DisplayModeString[intVal]);
			break;
		}
		case bmdDeckLinkStatusCurrentVideoInputPixelFormat:
		{
			printf("%-40s: %s\n", "Current Video Input PixFmt", PixelFormatString[intVal]);
			break;
		}
		case bmdDeckLinkStatusCurrentVideoInputFlags:
		{
			printf("%-40s: ", "Current Video Input Flags");
			if (intVal & bmdDeckLinkVideoStatusPsF) std::cout << "[PsF]";
			if (intVal & bmdDeckLinkVideoStatusDualStream3D) std::cout << "[3D]";
			std::cout << std::endl;
			break;
		}
		case bmdDeckLinkStatusCurrentVideoOutputMode:
		{
			printf("%-40s: %s\n", "Current Video Output Mode", DisplayModeString[intVal]);
			break;
		}
		case bmdDeckLinkStatusCurrentVideoOutputFlags:
		{
			printf("%-40s: ", "Current Video Output Flags");
			if (intVal & bmdDeckLinkVideoStatusPsF) std::cout << "[PsF]";
			if (intVal & bmdDeckLinkVideoStatusDualStream3D) std::cout << "[3D]";
			std::cout << std::endl;
			break;
		}
		case bmdDeckLinkStatusPCIExpressLinkWidth:
		{
			printf("%-40s: %d\n", "PCI-E Link Width", intVal);
			break;
		}
		case bmdDeckLinkStatusPCIExpressLinkSpeed:
		{
			printf("%-40s: %d\n", "PCI-E Link Speed", intVal);
			break;
		}
		case bmdDeckLinkStatusLastVideoOutputPixelFormat:
		{
			printf("%-40s: %s\n", "Last Video Output PixFmt", PixelFormatString[intVal]);
			break;
		}
		case bmdDeckLinkStatusReferenceSignalMode:
		{
			printf("%-40s: %d\n", "Ref Signal Mode", DisplayModeString[intVal]);
			break;
		}
		case bmdDeckLinkStatusReferenceSignalFlags:
		{
			printf("%-40s: ", "Ref Signal Flags");
			if (intVal & bmdDeckLinkVideoStatusPsF) std::cout << "[PsF]";
			if (intVal & bmdDeckLinkVideoStatusDualStream3D) std::cout << "[3D]";
			std::cout << std::endl;
			break;
		}
		case bmdDeckLinkStatusBusy:
		{
			printf("%-40s: ", "Busy");
			if (intVal == 0) printf("Idle");
			else
			{
				if (intVal & bmdDeviceCaptureBusy) printf("[Capture Busy]");
				if (intVal & bmdDevicePlaybackBusy) printf("[Playback Busy]");
				if (intVal & bmdDeviceSerialPortBusy) printf("[Serial Port Busy]");
			}
			printf("\n");
			break;
		}
		case bmdDeckLinkStatusInterchangeablePanelType:
		{
			printf("%-40s: %s\n", "Interchangeable Panel Type", PanelTypeString[intVal]);
			break;
		}
		case bmdDeckLinkStatusDeviceTemperature:
		{
			printf("%-40s: %d\n", "Device Temperature", intVal);
			break;
		}
		case bmdDeckLinkStatusVideoInputSignalLocked:
		{
			printf("%-40s: %s\n", "Video Input Signal Locked", BoonleanString[!!boolVal]);
			break;
		}
		case bmdDeckLinkStatusReferenceSignalLocked:
		{
			printf("%-40s: %s\n", "Ref Signal Locked", BoonleanString[!!boolVal]);
			break;
		}
		case bmdDeckLinkStatusReceivedEDID:
		{
			printf("%-40s: %s\n", "Received EDID", BoonleanString[!!boolVal]);
			break;
		}
		default:
			break;
		}
	}
}

const char* Decklink::GetDisplayModeNameFromEnum(BMDDisplayMode displayModeEnum)
{

}
