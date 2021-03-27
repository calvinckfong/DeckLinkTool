/*
 * decklink.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#include "decklink.h"
#include "const.h"
#include <iostream>

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
		char *displayName;
		deckLink->GetModelName((const char**)&modelName);
		deckLink->GetDisplayName((const char**)&displayName);
		//std::cout << deviceCount << ": " << modelName << std::endl;
		m_deckLinkDeviceList.push_back(deckLink);
		m_deckLinkDeviceModelName.push_back(modelName);
		m_deckLinkDeviceDisplayName.push_back(displayName);

		deviceCount++;
	}
	std::cout << deviceCount << " DeckLink devices found." << std::endl;
	std::cout << std::endl;

	return true;
}

void Decklink::ListDevices()
{
	std::cout << "====== Device List ======" << std::endl;
	printf("ID\tModel name\tDisplay name\n");
	for (size_t i=0; i<m_deckLinkDeviceList.size(); i++)
	{
		printf("%2ld\t%s\t%s\n", i, m_deckLinkDeviceModelName[i], m_deckLinkDeviceDisplayName[i]);
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
			std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceDisplayName[deviceId] << std::endl;

			ShowAttribute(deckLinkAttributes, BMDDeckLinkProfileID);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkDeviceInterface);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkNumberOfSubDevices);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSubDeviceIndex);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkPersistentID);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkDeviceGroupID);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkTopologicalID);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoIOSupport);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoInputConnections);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoOutputConnections);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoInputGainMinimum);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoInputGainMaximum);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoOutputGainMinimum);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVideoOutputGainMaximum);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkAudioInputConnections);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkAudioOutputConnections);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkMaximumAudioChannels);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkMaximumAnalogAudioInputChannels);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkMaximumAnalogAudioOutputChannels);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkAudioInputRCAChannelCount);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkAudioInputXLRChannelCount);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkAudioOutputRCAChannelCount);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkAudioOutputXLRChannelCount);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkMicrophoneInputGainMinimum);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkMicrophoneInputGainMaximum);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkDuplex);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkHasReferenceInput);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkHasSerialPort);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkHasAnalogVideoOutputGain);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkHasVideoInputAntiAliasingFilter);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkHasBypass);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkHasLTCTimecodeInput);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsInputFormatDetection);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsHDRMetadata);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsColorspaceMetadata);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsHDMITimecode);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsDualLinkSDI);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsQuadLinkSDI);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkSupportsIdleOutput);

			ShowAttribute(deckLinkAttributes, BMDDeckLinkSerialPortDeviceName);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkVendorName);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkDisplayName);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkModelName);
			ShowAttribute(deckLinkAttributes, BMDDeckLinkDeviceHandle);

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
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceDisplayName[deviceId] << std::endl;

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
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceDisplayName[deviceId] << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkConfiguration, (void**)&deckLinkConfiguration);
		if (result==S_OK)
		{
#if 1
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigSwapSerialRxTx);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeckControlConnection);

			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigHDMI3DPackingFormat);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigBypass);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigClockTimingAdjustment);

			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigVideoInputConnection);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigVideoInputScanning);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigVideoInputConversionMode);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigAnalogVideoInputFlags);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigCapture1080pAsPsF);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigCapturePassThroughMode);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigCaptureGroup);

			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigFieldFlickerRemoval);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigHD1080p24ToHD1080i5994Conversion);

			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigVideoOutputConnection);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDefaultVideoOutputMode);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDefaultVideoOutputModeFlags);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigVideoOutputConversionMode);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigRec2020Output);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfig444SDIVideoOutput);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigBlackVideoOutputDuringCapture);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigLowLatencyVideoOutput);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigOutput1080pAsPsF);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigVideoOutputIdleOperation);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigSDIOutputLinkConfiguration);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigHDMITimecodePacking);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigPlaybackGroup);

			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeviceInformationLabel);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeviceInformationSerialNumber);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeviceInformationCompany);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeviceInformationPhone);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeviceInformationEmail);
			ShowConfig(deckLinkConfiguration, bmdDeckLinkConfigDeviceInformationDate);

#else
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
#endif
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
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceDisplayName[deviceId] << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkStatus, (void**)&deckLinkStatus);
		if (result==S_OK)
		{
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusBusy);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusPCIExpressLinkWidth);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusPCIExpressLinkSpeed);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusInterchangeablePanelType);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusDetectedVideoInputMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusDetectedVideoInputFlags);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusVideoInputSignalLocked);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoInputMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoInputPixelFormat);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoInputFlags);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoOutputMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusCurrentVideoOutputFlags);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusLastVideoOutputPixelFormat);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReferenceSignalMode);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReferenceSignalFlags);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReferenceSignalLocked);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusDeviceTemperature);
			ShowStatus(deckLinkStatus, bmdDeckLinkStatusReceivedEDID);
			std::cout << std::endl;
		}
	}
}

void Decklink::ScanSignal(uint32_t deviceId)
{
	HRESULT result;
	IDeckLinkProfileAttributes* deckLinkAttributes = NULL;
	IDeckLink* deckLinkInput = NULL;
	bool supportIFD;

	if (deviceId<m_deckLinkDeviceList.size())
	{
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceDisplayName[deviceId] << std::endl;

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkProfileAttributes, (void**)&deckLinkAttributes);
		if (result != S_OK)
	    {
			fprintf(stderr, "Unable to open profile attribute interface (0x%08x)\n", result);
			goto fail;
		}

		result = deckLinkAttributes->GetFlag(BMDDeckLinkSupportsInputFormatDetection, &supportIFD);
		if ((result != S_OK) || (supportIFD == false))
		{
			fprintf(stderr, "Device does not support automatic mode detection\n");
			goto fail;
		}

		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkInput, (void**)&deckLinkInput);
		if (result != S_OK)
		{
			fprintf(stderr, "Could not obtain the IDeckLinkInput interface - result = %08x\n", result);
			goto fail;
		}

		// Todo

fail:
		;
	}
}

void Decklink::ShowAttribute(IDeckLinkProfileAttributes* deckLinkAttributes, BMDDeckLinkAttributeID attributeID)
{
	HRESULT	result;
	bool 		boolVal = false;
	int64_t	intVal = 0;
	double	floatVal = 0.0;
	const char*	stringVal;

	switch (attributeID) {
	// Flags
	case BMDDeckLinkSupportsInternalKeying:
	case BMDDeckLinkSupportsExternalKeying:
	case BMDDeckLinkSupportsInputFormatDetection:
	case BMDDeckLinkHasReferenceInput:
	case BMDDeckLinkHasSerialPort:
	case BMDDeckLinkHasAnalogVideoOutputGain:
	case BMDDeckLinkCanOnlyAdjustOverallVideoOutputGain:
	case BMDDeckLinkHasVideoInputAntiAliasingFilter:
	case BMDDeckLinkHasBypass:
	case BMDDeckLinkSupportsClockTimingAdjustment:
	case BMDDeckLinkSupportsFullFrameReferenceInputTimingOffset:
	case BMDDeckLinkSupportsSMPTELevelAOutput:
	case BMDDeckLinkSupportsDualLinkSDI:
	case BMDDeckLinkSupportsQuadLinkSDI:
	case BMDDeckLinkSupportsIdleOutput:
	case BMDDeckLinkVANCRequires10BitYUVVideoFrames:
	case BMDDeckLinkHasLTCTimecodeInput:
	case BMDDeckLinkSupportsHDRMetadata:
	case BMDDeckLinkSupportsColorspaceMetadata:
	case BMDDeckLinkSupportsHDMITimecode:
	case BMDDeckLinkSupportsHighFrameRateTimecode:
	case BMDDeckLinkSupportsSynchronizeToCaptureGroup:
	case BMDDeckLinkSupportsSynchronizeToPlaybackGroup:
		result = deckLinkAttributes->GetFlag(attributeID, &boolVal);
		break;

		// Integers
	case BMDDeckLinkMaximumAudioChannels:
	case BMDDeckLinkMaximumAnalogAudioInputChannels:
	case BMDDeckLinkMaximumAnalogAudioOutputChannels:
	case BMDDeckLinkNumberOfSubDevices:
	case BMDDeckLinkSubDeviceIndex:
	case BMDDeckLinkPersistentID:
	case BMDDeckLinkDeviceGroupID:
	case BMDDeckLinkTopologicalID:
	case BMDDeckLinkVideoOutputConnections:
	case BMDDeckLinkVideoInputConnections:
	case BMDDeckLinkAudioOutputConnections:
	case BMDDeckLinkAudioInputConnections:
	case BMDDeckLinkVideoIOSupport:
	case BMDDeckLinkDeckControlConnections:
	case BMDDeckLinkDeviceInterface:
	case BMDDeckLinkAudioInputRCAChannelCount:
	case BMDDeckLinkAudioInputXLRChannelCount:
	case BMDDeckLinkAudioOutputRCAChannelCount:
	case BMDDeckLinkAudioOutputXLRChannelCount:
	case BMDDeckLinkProfileID:
	case BMDDeckLinkDuplex:
		result = deckLinkAttributes->GetInt(attributeID, &intVal);
		break;

		// Floats
	case BMDDeckLinkVideoInputGainMinimum:
	case BMDDeckLinkVideoInputGainMaximum:
	case BMDDeckLinkVideoOutputGainMinimum:
	case BMDDeckLinkVideoOutputGainMaximum:
	case BMDDeckLinkMicrophoneInputGainMinimum:
	case BMDDeckLinkMicrophoneInputGainMaximum:
		result = deckLinkAttributes->GetFloat(attributeID, &floatVal);
		break;

		// Strings
	case BMDDeckLinkSerialPortDeviceName:
	case BMDDeckLinkVendorName:
	case BMDDeckLinkDisplayName:
	case BMDDeckLinkModelName:
	case BMDDeckLinkDeviceHandle:
		result = deckLinkAttributes->GetString(attributeID, &stringVal);
		break;

	default:
		return;
	}

	if (result == S_OK)
	{
		switch (attributeID) {
		// Flags
		case BMDDeckLinkSupportsInternalKeying:
			printf(" %-30s: %s\n", "Support Internal Keying", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsExternalKeying:
			printf(" %-30s: %s\n", "Support External Keying", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsInputFormatDetection:
			printf(" %-30s: %s\n", "Support Input Format Detect", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsClockTimingAdjustment:
			printf(" %-30s: %s\n", "Support Clock Timing Adjust", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsFullFrameReferenceInputTimingOffset:
			printf(" %-30s: %s\n", "Support FF Ref Input Timing", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsSMPTELevelAOutput:
			printf(" %-30s: %s\n", "Support SMPTE Level A Output", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsDualLinkSDI:
			printf(" %-30s: %s\n", "Support Dual Link SDI", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsQuadLinkSDI:
			printf(" %-30s: %s\n", "Support Quad Link SDI", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsIdleOutput:
			printf(" %-30s: %s\n", "Support Idle Output", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsHDRMetadata:
			printf(" %-30s: %s\n", "Support HDR Metadata", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsColorspaceMetadata:
			printf(" %-30s: %s\n", "Support Colorspace Metadata", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsHDMITimecode:
			printf(" %-30s: %s\n", "Support HDMI Timecode", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsHighFrameRateTimecode:
			printf(" %-30s: %s\n", "Support HFR Timecode", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsSynchronizeToCaptureGroup:
			printf(" %-30s: %s\n", "Support Synchronize to Capture Group", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkSupportsSynchronizeToPlaybackGroup:
			printf(" %-30s: %s\n", "Support Synchronize to Playback Group", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkHasReferenceInput:
			printf(" %-30s: %s\n", "Has Ref Input", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkHasSerialPort:
			printf(" %-30s: %s\n", "Has Serial Port", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkHasAnalogVideoOutputGain:
			printf(" %-30s: %s\n", "Has Analog Video Output Gain", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkHasVideoInputAntiAliasingFilter:
			printf(" %-30s: %s\n", "Has Video Input AA Filter", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkHasBypass:
			printf(" %-30s: %s\n", "Has Bypass", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkHasLTCTimecodeInput:
			printf(" %-30s: %s\n", "Has LTC Timecode Input", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkCanOnlyAdjustOverallVideoOutputGain:
			printf(" %-30s: %s\n", "Can Only Adjust Overall Video Output Gain", BooleanString[!!boolVal]);
			break;

		case BMDDeckLinkVANCRequires10BitYUVVideoFrames:
			printf(" %-30s: %s\n", "VANC Requires 10-Bit YUV", BooleanString[!!boolVal]);
			break;


			// Integers
		case BMDDeckLinkMaximumAudioChannels:
			printf(" %-30s: %ld\n", "Max Audio Channels", intVal);
			break;

		case BMDDeckLinkMaximumAnalogAudioInputChannels:
			printf(" %-30s: %ld\n", "Max Analog Audio Input Channels", intVal);
			break;

		case BMDDeckLinkMaximumAnalogAudioOutputChannels:
			printf(" %-30s: %ld\n", "Max Analog Audio Output Channels", intVal);
			break;

		case BMDDeckLinkNumberOfSubDevices:
			printf(" %-30s: %ld\n", "# of Sub-devices", intVal);
			break;

		case BMDDeckLinkSubDeviceIndex:
			printf(" %-30s: %ld\n", "Sub-device index", intVal);
			break;

		case BMDDeckLinkPersistentID:
			printf(" %-30s: %ld\n", "Persistent ID", intVal);
			break;

		case BMDDeckLinkDeviceGroupID:
			printf(" %-30s: %ld\n", "Device Group ID", intVal);
			break;

		case BMDDeckLinkTopologicalID:
			printf(" %-30s: 0x%08x\n", "Topological ID", intVal);
			break;


		case BMDDeckLinkVideoOutputConnections:
			printf(" %-30s: ", "Video Output Connection");
			if (intVal==0)	std::cout << "[Unspecified]";
			else {
				for (size_t i=0; i<6; i++)
					if (intVal & (1<<i))	std::cout << VideoConnectionString[i];
			}
			std::cout << std::endl;
			break;

		case BMDDeckLinkVideoInputConnections:
			printf(" %-30s: ", "Video Input Connection");
			if (intVal==0)	std::cout << "[Unspecified]";
			else {
				for (size_t i=0; i<6; i++)
					if (intVal & (1<<i))	std::cout << VideoConnectionString[i];
			}
			std::cout << std::endl;
			break;

		case BMDDeckLinkAudioOutputConnections:
			printf(" %-30s: ", "Audio Output Connection");
			if (intVal==0)	std::cout << "[Unspecified]";
			else {
				for (size_t i=0; i<6; i++)
					if (intVal & (1<<i))	std::cout << AudioConnectionString[i];
			}
			std::cout << std::endl;
			break;

		case BMDDeckLinkAudioInputConnections:
			printf(" %-30s: ", "Audio Intput Connection");
			if (intVal==0)	std::cout << "[Unspecified]";
			else {
				for (size_t i=0; i<6; i++)
					if (intVal & (1<<i))	std::cout << AudioConnectionString[i];
			}
			std::cout << std::endl;
			break;

		case BMDDeckLinkVideoIOSupport:
			printf(" %-30s: %s\n", "Allow Capture",  BooleanString[!!(intVal&bmdDeviceSupportsCapture)]);
			printf(" %-30s: %s\n", "Aloow Playback", BooleanString[!!(intVal&bmdDeviceSupportsPlayback)]);
			break;

		case BMDDeckLinkDeckControlConnections:
			printf(" %-30s: ", "Control Connection");
			if ( intVal & bmdDeckControlConnectionRS422Remote1) std::cout << "RS-422 Remote 1 ";
			if ( intVal & bmdDeckControlConnectionRS422Remote2) std::cout << "RS-422 Remote 2 ";
			std::cout << std::endl;
			break;

		case BMDDeckLinkDeviceInterface:
			printf(" %-30s: %s\n", "Device Interface",  DeviceInterfaceString[intVal]);
			break;

		case BMDDeckLinkAudioInputRCAChannelCount:
			printf(" %-30s: %ld\n", "#Audio Input RCA Channel",  intVal);
			break;

		case BMDDeckLinkAudioInputXLRChannelCount:
			printf(" %-30s: %ld\n", "#Audio Input XLR Channel",  intVal);
			break;

		case BMDDeckLinkAudioOutputRCAChannelCount:
			printf(" %-30s: %ld\n", "#Audio Output RCA Channel",  intVal);
			break;

		case BMDDeckLinkAudioOutputXLRChannelCount:
			printf(" %-30s: %ld\n", "#Audio Output XLR Channel",  intVal);
			break;

		case BMDDeckLinkProfileID:
			if (intVal!=0)
				printf(" %-30s: %s\n", "ProfileID",  ProfileIDString[intVal]);
			break;

		case BMDDeckLinkDuplex:
			printf(" %-30s: %s\n", "Duplex",  DuplexModeString[intVal]);
			break;

			// Floats
		case BMDDeckLinkVideoInputGainMinimum:
			printf(" %-30s: %lf\n", "Min Video Input Gain",  floatVal);
			break;

		case BMDDeckLinkVideoInputGainMaximum:
			printf(" %-30s: %lf\n", "Max Video Input Gain",  floatVal);
			break;

		case BMDDeckLinkVideoOutputGainMinimum:
			printf(" %-30s: %lf\n", "Min Video Output Gain",  floatVal);
			break;

		case BMDDeckLinkVideoOutputGainMaximum:
			printf(" %-30s: %lf\n", "Max Video Output Gain",  floatVal);
			break;

		case BMDDeckLinkMicrophoneInputGainMinimum:
			printf(" %-30s: %lf\n", "Min Mic Input Gain",  floatVal);
			break;

		case BMDDeckLinkMicrophoneInputGainMaximum:
			printf(" %-30s: %lf\n", "Max Mic Output Gain",  floatVal);
			break;

			// Strings
		case BMDDeckLinkSerialPortDeviceName:
			printf(" %-30s: %s\n", "Serial Port Device Name",  stringVal);
			break;

		case BMDDeckLinkVendorName:
			printf(" %-30s: %s\n", "Vendor Name",  stringVal);
			break;

		case BMDDeckLinkDisplayName:
			printf(" %-30s: %s\n", "Display Name",  stringVal);
			break;

		case BMDDeckLinkModelName:
			printf(" %-30s: %s\n", "Model Name",  stringVal);
			break;

		case BMDDeckLinkDeviceHandle:
			printf(" %-30s: %s\n", "Device Handle",  stringVal);
			break;

		default:
			break;
		}
	}
}

void Decklink::ShowConfig(IDeckLinkConfiguration* deckLinkConfiguration, BMDDeckLinkConfigurationID configID)
{
	HRESULT	result = -1;
	bool 		boolVal = false;
	int64_t	intVal = 0;
	double	floatVal = 0.0;
	const char*	stringVal;

	switch (configID) {
	// Serial port Flags
	case bmdDeckLinkConfigSwapSerialRxTx:
	// Audio Input/Output Flags
	case bmdDeckLinkConfigAnalogAudioConsumerLevels:
	// Video output flags
	case bmdDeckLinkConfigFieldFlickerRemoval:
	case bmdDeckLinkConfigHD1080p24ToHD1080i5994Conversion:
	case bmdDeckLinkConfig444SDIVideoOutput:
	case bmdDeckLinkConfigBlackVideoOutputDuringCapture:
	case bmdDeckLinkConfigLowLatencyVideoOutput:
	case bmdDeckLinkConfigDownConversionOnAllAnalogOutput:
	case bmdDeckLinkConfigSMPTELevelAOutput:
	case bmdDeckLinkConfigRec2020Output:
	case bmdDeckLinkConfigQuadLinkSDIVideoOutputSquareDivisionSplit:
	case bmdDeckLinkConfigOutput1080pAsPsF:
	// Video Input Flags
	case bmdDeckLinkConfigVideoInputScanning:
	case bmdDeckLinkConfigUseDedicatedLTCInput:
	case bmdDeckLinkConfigSDIInput3DPayloadOverride:
	case bmdDeckLinkConfigCapture1080pAsPsF:
	// Audio Input Flags
	case bmdDeckLinkConfigMicrophonePhantomPower:
		result = deckLinkConfiguration->GetFlag(configID, &boolVal);
		break;

	// Video Input/Output Integers
	case bmdDeckLinkConfigHDMI3DPackingFormat:
	case bmdDeckLinkConfigBypass:
	case bmdDeckLinkConfigClockTimingAdjustment:
	// Video Output Integers
	case bmdDeckLinkConfigVideoOutputConnection:
	case bmdDeckLinkConfigVideoOutputConversionMode:
	case bmdDeckLinkConfigAnalogVideoOutputFlags:
	case bmdDeckLinkConfigReferenceInputTimingOffset:
	case bmdDeckLinkConfigVideoOutputIdleOperation:
	case bmdDeckLinkConfigDefaultVideoOutputMode:
	case bmdDeckLinkConfigDefaultVideoOutputModeFlags:
	case bmdDeckLinkConfigSDIOutputLinkConfiguration:
	case bmdDeckLinkConfigHDMITimecodePacking:
	case bmdDeckLinkConfigPlaybackGroup:
	// Video Input Integers
	case bmdDeckLinkConfigVideoInputConnection:
	case bmdDeckLinkConfigAnalogVideoInputFlags:
	case bmdDeckLinkConfigVideoInputConversionMode:
	case bmdDeckLinkConfig32PulldownSequenceInitialTimecodeFrame:
	case bmdDeckLinkConfigVANCSourceLine1Mapping:
	case bmdDeckLinkConfigVANCSourceLine2Mapping:
	case bmdDeckLinkConfigVANCSourceLine3Mapping:
	case bmdDeckLinkConfigCapturePassThroughMode:
	case bmdDeckLinkConfigCaptureGroup:
	// Audio Input Integers
	case bmdDeckLinkConfigAudioInputConnection:
	// Audio Output Integers
	case bmdDeckLinkConfigAudioOutputAESAnalogSwitch:
	// Deck Control Integers
	case bmdDeckLinkConfigDeckControlConnection:
		result = deckLinkConfiguration->GetInt(configID, &intVal);
		break;

	// Video Output Floats
	case bmdDeckLinkConfigVideoOutputComponentLumaGain:
	case bmdDeckLinkConfigVideoOutputComponentChromaBlueGain:
	case bmdDeckLinkConfigVideoOutputComponentChromaRedGain:
	case bmdDeckLinkConfigVideoOutputCompositeLumaGain:
	case bmdDeckLinkConfigVideoOutputCompositeChromaGain:
	case bmdDeckLinkConfigVideoOutputSVideoLumaGain:
	case bmdDeckLinkConfigVideoOutputSVideoChromaGain:
	// Video Input Floats
	case bmdDeckLinkConfigVideoInputComponentLumaGain:
	case bmdDeckLinkConfigVideoInputComponentChromaBlueGain:
	case bmdDeckLinkConfigVideoInputComponentChromaRedGain:
	case bmdDeckLinkConfigVideoInputCompositeLumaGain:
	case bmdDeckLinkConfigVideoInputCompositeChromaGain:
	case bmdDeckLinkConfigVideoInputSVideoLumaGain:
	case bmdDeckLinkConfigVideoInputSVideoChromaGain:
	// Audio Input Floats
	case bmdDeckLinkConfigAnalogAudioInputScaleChannel1:
	case bmdDeckLinkConfigAnalogAudioInputScaleChannel2:
	case bmdDeckLinkConfigAnalogAudioInputScaleChannel3:
	case bmdDeckLinkConfigAnalogAudioInputScaleChannel4:
	case bmdDeckLinkConfigDigitalAudioInputScale:
	case bmdDeckLinkConfigMicrophoneInputGain:
	// Audio Output Floats
	case bmdDeckLinkConfigAnalogAudioOutputScaleChannel1:
	case bmdDeckLinkConfigAnalogAudioOutputScaleChannel2:
	case bmdDeckLinkConfigAnalogAudioOutputScaleChannel3:
	case bmdDeckLinkConfigAnalogAudioOutputScaleChannel4:
	case bmdDeckLinkConfigDigitalAudioOutputScale:
	case bmdDeckLinkConfigHeadphoneVolume:
		result = deckLinkConfiguration->GetFloat(configID, &floatVal);
		break;

	// Device Information Strings
	case bmdDeckLinkConfigDeviceInformationLabel:
	case bmdDeckLinkConfigDeviceInformationSerialNumber:
	case bmdDeckLinkConfigDeviceInformationCompany:
	case bmdDeckLinkConfigDeviceInformationPhone:
	case bmdDeckLinkConfigDeviceInformationEmail:
	case bmdDeckLinkConfigDeviceInformationDate:
		result = deckLinkConfiguration->GetString(configID, &stringVal);
		break;

	default:
		break;
	}

	if (result == S_OK)
	{
		switch (configID) {
		// Serial port Flags
		case bmdDeckLinkConfigSwapSerialRxTx:
			printf(" %-30s: %s\n", "Swap Serial Rx/Tx", BooleanString[!!boolVal]);
			break;

		// Audio Input/Output Flags
		case bmdDeckLinkConfigAnalogAudioConsumerLevels:
			printf(" %-30s: %s\n", "Analog Audio Consumer Level", BooleanString[!!boolVal]);
			break;

		// Video output flags
		case bmdDeckLinkConfigFieldFlickerRemoval:
			printf(" %-30s: %s\n", "Field Flicker Removal", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigHD1080p24ToHD1080i5994Conversion:
			printf(" %-30s: %s\n", "1080p24 to 1080i 59.94 conversion", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfig444SDIVideoOutput:
			printf(" %-30s: %s\n", "YUV444 SDI Video Output", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigBlackVideoOutputDuringCapture:
			printf(" %-30s: %s\n", "Black Video Output During Capture", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigLowLatencyVideoOutput:
			printf(" %-30s: %s\n", "Low-Latency Video Output", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigDownConversionOnAllAnalogOutput:
			printf(" %-30s: %s\n", "Down Conversion On All Analog Output", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigSMPTELevelAOutput:
			printf(" %-30s: %s\n", "SMPTE Level A Output", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigRec2020Output:
			printf(" %-30s: %s\n", "Rec.2020 Output", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigQuadLinkSDIVideoOutputSquareDivisionSplit:
			printf(" %-30s: %s\n", "Quad-Link SDI Video Output Square Division Split", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigOutput1080pAsPsF:
			printf(" %-30s: %s\n", "1080p As PsF", BooleanString[!!boolVal]);
			break;

		// Video Input Flags
		case bmdDeckLinkConfigVideoInputScanning:
			printf(" %-30s: %s\n", "Video Input Scanning", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigUseDedicatedLTCInput:
			printf(" %-30s: %s\n", "Use Dedicated LTC Input", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigSDIInput3DPayloadOverride:
			printf(" %-30s: %s\n", "SDI Input 3D Payload Override", BooleanString[!!boolVal]);
			break;

		case bmdDeckLinkConfigCapture1080pAsPsF:
			printf(" %-30s: %s\n", "Capture 1080p As PsF", BooleanString[!!boolVal]);
			break;

		// Audio Input Flags
		case bmdDeckLinkConfigMicrophonePhantomPower:
			printf(" %-30s: %s\n", "Microphone Phantom Power", BooleanString[!!boolVal]);
			break;

		// Video Input/Output Integers
		case bmdDeckLinkConfigHDMI3DPackingFormat:
			printf(" %-30s: %s\n", "HDMI 3D Packing Format", Video3DPackingFormatString[intVal]);
			break;

		case bmdDeckLinkConfigBypass:
			printf(" %-30s: %ld\n", "Bypass", intVal);
			break;

		case bmdDeckLinkConfigClockTimingAdjustment:
			printf(" %-30s: %ld\n", "Clock Timing Adjustment", intVal);
			break;

		// Video Output Integers
		case bmdDeckLinkConfigVideoOutputConnection:
			printf(" %-30s: ", "Video Output Connection");
			for (int i=0; i<6; i++)
				if (intVal&(1<<i))	std::cout << VideoConnectionString[i];
			std::cout << std::endl;
			break;

		case bmdDeckLinkConfigVideoOutputConversionMode:
			printf(" %-30s: %s\n", "Video Output Conversion Mode", VideoOutputConversionModeString[intVal]);
			break;

		case bmdDeckLinkConfigAnalogVideoOutputFlags:
			printf(" %-30s: ", "Analog Video Output Flags");
			if (intVal & bmdAnalogVideoFlagCompositeSetup75) std::cout << "[Composite Setup 75]";
			if (intVal & bmdAnalogVideoFlagComponentBetacamLevels) std::cout << "[Component Betacam Levels]";
			std::cout << std::endl;
			break;

		case bmdDeckLinkConfigReferenceInputTimingOffset:
			printf(" %-30s: %ld\n", "Reference Input Timing Offset", intVal);
			break;

		case bmdDeckLinkConfigVideoOutputIdleOperation:
			printf(" %-30s: %s\n", "Video Output Idle Operation", VideoOutputOpearationString[intVal]);
			break;

		case bmdDeckLinkConfigDefaultVideoOutputMode:
			printf(" %-30s: %s\n", "Default Video Output Mode", DisplayModeString[intVal]);
			break;

		case bmdDeckLinkConfigDefaultVideoOutputModeFlags:
			printf(" %-30s: 0x%08x\n", "Default Video Output Mode Flag", intVal);
			break;

		case bmdDeckLinkConfigSDIOutputLinkConfiguration:
			printf(" %-30s: %s\n", "SDI Output Link Configuration", LinkConfigurationString[intVal]);
			break;

		case bmdDeckLinkConfigHDMITimecodePacking:
			printf(" %-30s: %s\n", "HDMI Timecode Packing", HDMITimecodePackingString[intVal]);
			break;

		case bmdDeckLinkConfigPlaybackGroup:
			printf(" %-30s: 0x%08x\n", "Playback Group", intVal);
			break;

		// Video Input Integers
		case bmdDeckLinkConfigVideoInputConnection:
			printf(" %-30s: ", "Video Input Connection");
			for (int i=0; i<6; i++)
				if (intVal&(1<<i))	std::cout << VideoConnectionString[i];
			std::cout << std::endl;
			break;

		case bmdDeckLinkConfigAnalogVideoInputFlags:
			printf(" %-30s: ", "Analog Video Input Flags");
			if (intVal & bmdAnalogVideoFlagCompositeSetup75) std::cout << "[Composite Setup 75]";
			if (intVal & bmdAnalogVideoFlagComponentBetacamLevels) std::cout << "[Component Betacam Levels]";
			std::cout << std::endl;
			break;

		case bmdDeckLinkConfigVideoInputConversionMode:
			printf(" %-30s: %s\n", "Video Input Conversion Mode", VideoInputConversionModeString[intVal]);
			break;

		case bmdDeckLinkConfig32PulldownSequenceInitialTimecodeFrame:
		case bmdDeckLinkConfigVANCSourceLine1Mapping:
		case bmdDeckLinkConfigVANCSourceLine2Mapping:
		case bmdDeckLinkConfigVANCSourceLine3Mapping:
			break;

		case bmdDeckLinkConfigCapturePassThroughMode:
			printf(" %-30s: %s\n", "Capture Pass Through Mode", CapturePassThroughMode[intVal]);
			break;

		case bmdDeckLinkConfigCaptureGroup:
			printf(" %-30s: 0x%08x\n", "Capture Group", intVal);
			break;

		// Audio Input Integers
		case bmdDeckLinkConfigAudioInputConnection:
			printf(" %-30s: ", "Audio Input Connection");
			for (int i=0; i<7; i++)
				if (intVal&(1<<i))	std::cout << AudioConnectionString[i];
			std::cout << std::endl;
			break;

		// Audio Output Integers
		case bmdDeckLinkConfigAudioOutputAESAnalogSwitch:
			break;

		// Deck Control Integers
		case bmdDeckLinkConfigDeckControlConnection:
			printf(" %-30s: ", "Deck Control Connection");
			if ( intVal & bmdDeckControlConnectionRS422Remote1) std::cout << "RS-422 Remote 1 ";
			if ( intVal & bmdDeckControlConnectionRS422Remote2) std::cout << "RS-422 Remote 2 ";
			std::cout << std::endl;
			break;

		// Video Output Floats
		case bmdDeckLinkConfigVideoOutputComponentLumaGain:
		case bmdDeckLinkConfigVideoOutputComponentChromaBlueGain:
		case bmdDeckLinkConfigVideoOutputComponentChromaRedGain:
		case bmdDeckLinkConfigVideoOutputCompositeLumaGain:
		case bmdDeckLinkConfigVideoOutputCompositeChromaGain:
		case bmdDeckLinkConfigVideoOutputSVideoLumaGain:
		case bmdDeckLinkConfigVideoOutputSVideoChromaGain:
		// Video Input Floats
		case bmdDeckLinkConfigVideoInputComponentLumaGain:
		case bmdDeckLinkConfigVideoInputComponentChromaBlueGain:
		case bmdDeckLinkConfigVideoInputComponentChromaRedGain:
		case bmdDeckLinkConfigVideoInputCompositeLumaGain:
		case bmdDeckLinkConfigVideoInputCompositeChromaGain:
		case bmdDeckLinkConfigVideoInputSVideoLumaGain:
		case bmdDeckLinkConfigVideoInputSVideoChromaGain:
		// Audio Input Floats
		case bmdDeckLinkConfigAnalogAudioInputScaleChannel1:
		case bmdDeckLinkConfigAnalogAudioInputScaleChannel2:
		case bmdDeckLinkConfigAnalogAudioInputScaleChannel3:
		case bmdDeckLinkConfigAnalogAudioInputScaleChannel4:
		case bmdDeckLinkConfigDigitalAudioInputScale:
		case bmdDeckLinkConfigMicrophoneInputGain:
		// Audio Output Floats
		case bmdDeckLinkConfigAnalogAudioOutputScaleChannel1:
		case bmdDeckLinkConfigAnalogAudioOutputScaleChannel2:
		case bmdDeckLinkConfigAnalogAudioOutputScaleChannel3:
		case bmdDeckLinkConfigAnalogAudioOutputScaleChannel4:
		case bmdDeckLinkConfigDigitalAudioOutputScale:
		case bmdDeckLinkConfigHeadphoneVolume:
			break;

		// Device Information Strings
		case bmdDeckLinkConfigDeviceInformationLabel:
			printf(" %-30s: %s\n", "Label",  stringVal);
			break;

		case bmdDeckLinkConfigDeviceInformationSerialNumber:
			printf(" %-30s: %s\n", "Serial#",  stringVal);
			break;

		case bmdDeckLinkConfigDeviceInformationCompany:
			printf(" %-30s: %s\n", "Company",  stringVal);
			break;

		case bmdDeckLinkConfigDeviceInformationPhone:
			printf(" %-30s: %s\n", "Phone",  stringVal);
			break;

		case bmdDeckLinkConfigDeviceInformationEmail:
			printf(" %-30s: %s\n", "Email",  stringVal);
			break;

		case bmdDeckLinkConfigDeviceInformationDate:
			printf(" %-30s: %s\n", "Date",  stringVal);
			break;

		default:
			break;
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
			printf("%-40s: %ld\n", "PCI-E Link Width", intVal);
			break;
		}
		case bmdDeckLinkStatusPCIExpressLinkSpeed:
		{
			printf("%-40s: %ld\n", "PCI-E Link Speed", intVal);
			break;
		}
		case bmdDeckLinkStatusLastVideoOutputPixelFormat:
		{
			printf("%-40s: %s\n", "Last Video Output PixFmt", PixelFormatString[intVal]);
			break;
		}
		case bmdDeckLinkStatusReferenceSignalMode:
		{
			printf("%-40s: %s\n", "Ref Signal Mode", DisplayModeString[intVal]);
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
			printf("%-40s: %ld\n", "Device Temperature", intVal);
			break;
		}
		case bmdDeckLinkStatusVideoInputSignalLocked:
		{
			printf("%-40s: %s\n", "Video Input Signal Locked", BooleanString[!!boolVal]);
			break;
		}
		case bmdDeckLinkStatusReferenceSignalLocked:
		{
			printf("%-40s: %s\n", "Ref Signal Locked", BooleanString[!!boolVal]);
			break;
		}
		case bmdDeckLinkStatusReceivedEDID:
		{
			printf("%-40s: %s\n", "Received EDID", BooleanString[!!boolVal]);
			break;
		}
		default:
			break;
		}
	}
}
