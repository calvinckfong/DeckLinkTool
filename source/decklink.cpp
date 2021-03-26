/*
 * decklink.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#include "decklink.h"
#include <iostream>

const char* BoonleanString[2] = {"FALSE", "TRUE"};

const char* VideoConnectionString[7] = {
		"Unspecified", 	"SDI", 	"HDMI", "Optical SDI",
		"Component", 	"Composite", 	"SVideo"
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
		char *modelName;
		m_deckLinkDeviceList[i]->GetModelName((const char**)&modelName);
		std::cout << i << ": " << modelName << std::endl;
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

			std::cout << "Device " << deviceId << ":" << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkVideoInputConnections, &inPorts);
			std::cout << " Input Port: ";
			if (inPorts&bmdVideoConnectionSDI) 			std::cout << "[SDI] ";
			if (inPorts&bmdVideoConnectionHDMI)			std::cout << "[HDMI] ";
			if (inPorts&bmdVideoConnectionOpticalSDI) 	std::cout << "[Optical SDI] ";
			if (inPorts&bmdVideoConnectionComponent)	std::cout << "[Component] ";
			if (inPorts&bmdVideoConnectionComposite)	std::cout << "[Composite] ";
			if (inPorts&bmdVideoConnectionSVideo) 		std::cout << "[SVideo] ";
			std::cout << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkVideoOutputConnections, &outPorts);
			std::cout << " Output Port: ";
			if (outPorts&bmdVideoConnectionSDI) 		std::cout << "[SDI] ";
			if (outPorts&bmdVideoConnectionHDMI)		std::cout << "[HDMI] ";
			if (outPorts&bmdVideoConnectionOpticalSDI)	std::cout << "[Optical SDI] ";
			if (outPorts&bmdVideoConnectionComponent)	std::cout << "[Component] ";
			if (outPorts&bmdVideoConnectionComposite)	std::cout << "[Composite] ";
			if (outPorts&bmdVideoConnectionSVideo)		std::cout << "[SVideo] ";
			std::cout << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkVideoIOSupport, &videoIOSupport);
			std::cout << " Capture  " << BoonleanString[!!(videoIOSupport&bmdDeviceSupportsCapture)] << std::endl;
			std::cout << " Playback " << BoonleanString[!!(videoIOSupport&bmdDeviceSupportsPlayback)] << std::endl;

			deckLinkAttributes->GetInt(BMDDeckLinkDuplex, &duplex);
			std::cout << " Duplex   ";
			if (duplex == bmdDuplexFull) 			std::cout << "Full Duplex";
			else if (duplex == bmdDuplexHalf) 		std::cout << "Half Duplex";
			else if (duplex == bmdDuplexSimplex)	std::cout << "Simplex";
			else if (duplex == bmdDuplexInactive)	std::cout << "Inactive";
			std::cout << std::endl;

			deckLinkAttributes->GetFlag(BMDDeckLinkSupportsHDRMetadata, &supportHDRMetadata);
			std::cout << " HDR meta " << BoonleanString[supportHDRMetadata] << std::endl;
			deckLinkAttributes->GetFlag(BMDDeckLinkSupportsColorspaceMetadata, &supportColorspaceMetadata);
			std::cout << " CS meta  " << BoonleanString[supportColorspaceMetadata] << std::endl;

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

				std::cout << std::dec << modeCount << ": " << modeName << " (0x" << std::hex << bMDdisplayMode << ")" << std::endl;
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

				std::cout << std::dec << modeCount << ": " << modeName << " (0x" << std::hex << bMDdisplayMode << ")" << std::endl;
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
