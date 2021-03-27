/*
 * const.h
 *
 *  Created on: 2021年3月27日
 *      Author: calvin.fong
 */

#ifndef SOURCE_CONST_H_
#define SOURCE_CONST_H_

#include <map>

const char* BooleanString[2] = {"No", "Yes"};

const char* VideoConnectionString[7] = {
		"[Unspecified]", 	"[SDI]", 		"[HDMI]", "[Optical SDI]",
		"[Component]", 	"[Composite]", "[SVideo]"
};

const char* AudioConnectionString[7] = {
		"Embedded", "AES-EBU",
		"Analog", "Analog XLR", "Analog RCA",
		"Microphone", "Headphones"
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
	{bmdPanelNotDetected, 				"Not Detected"},
	{bmdPanelTeranexMiniSmartPanel,	"Teranex Mini Smart Panel"},
};

std::map<BMDProfileID, const char*> ProfileIDString =
{
		{bmdProfileOneSubDeviceFullDuplex, 		"1 Sub-device Full Duplex"},
		{bmdProfileOneSubDeviceHalfDuplex, 		"1 Sub-device Half Duplex"},
		{bmdProfileTwoSubDevicesFullDuplex, 	"2 Sub-device Full Duplex"},
		{bmdProfileTwoSubDevicesHalfDuplex, 	"2 Sub-device Half Duplex"},
		{bmdProfileFourSubDevicesHalfDuplex, 	"4 Sub-device Half Duplex"}
};

std::map<BMDHDMITimecodePacking, const char*> HDMITimecodePackingString =
{
		{bmdHDMITimecodePackingIEEEOUI000085,	"IEEE-OUI000085"},
		{bmdHDMITimecodePackingIEEEOUI080046,	"IEEE-OUI080046"},
		{bmdHDMITimecodePackingIEEEOUI5CF9F0,	"IEEE-OUI5CF9F0"}
};

std::map<BMDDuplexMode, const char*> DuplexModeString =
{
		{bmdDuplexFull, 		"Full Duplex"},
		{bmdDuplexHalf, 		"Half Duplex"},
		{bmdDuplexSimplex, 	"Simplex"},
		{bmdDuplexInactive,	"Inactive"}
};

std::map<BMDLinkConfiguration, const char*> LinkConfigurationString =
{
		{bmdLinkConfigurationSingleLink,	"Single Link"},
		{bmdLinkConfigurationDualLink,	"Dual Link"},
		{bmdLinkConfigurationQuadLink,	"Quad Link"},
};

std::map<BMDDeviceInterface, const char*> DeviceInterfaceString =
{
		{bmdDeviceInterfacePCI, "PCI"},
		{bmdDeviceInterfaceUSB, "USB"},
		{bmdDeviceInterfaceThunderbolt, "Thunderbolt"},
};

std::map<BMDVideo3DPackingFormat, const char*> Video3DPackingFormatString =
{
	{bmdVideo3DPackingSidebySideHalf,	"Side-by-side Half"},
	{bmdVideo3DPackingLinebyLine, 		"Line-by-line"},
	{bmdVideo3DPackingTopAndBottom,		"Top-and-bottom"},
	{bmdVideo3DPackingFramePacking,		"Frame Packing"},
	{bmdVideo3DPackingLeftOnly,			"Left Only"},
	{bmdVideo3DPackingRightOnly,			"Right Only"},
};

std::map<BMDVideoInputConversionMode, const char*> VideoInputConversionModeString =
{
	{bmdNoVideoInputConversion,								"No Converstion"},
	{bmdVideoInputLetterboxDownconversionFromHD1080,	"Letter-box Down-conversion From HD-1080"},
	{bmdVideoInputAnamorphicDownconversionFromHD1080,	"Anamorphic Down-conversion From HD-1080"},
	{bmdVideoInputLetterboxDownconversionFromHD720,		"Letter-box Down-conversion From HD-720"},
	{bmdVideoInputAnamorphicDownconversionFromHD720,	"Anamorphic Down-conversion From HD-720"},
	{bmdVideoInputLetterboxUpconversion,					"Letter-box Up-conversion"},
	{bmdVideoInputAnamorphicUpconversion,					"Anamorphic Up-conversion"}
};

std::map<BMDVideoOutputConversionMode, const char*> VideoOutputConversionModeString =
{
		{bmdNoVideoOutputConversion,					"No conversion"},
		{bmdVideoOutputLetterboxDownconversion,	"Letter box Down-conversion"},
		{bmdVideoOutputAnamorphicDownconversion,	"Anamorphic Down-conversion"},
		{bmdVideoOutputHD720toHD1080Conversion,	"HD-720 to HD-1080 Conversion"},
		{bmdVideoOutputHardwareLetterboxDownconversion,				"Hardware Letter box Down-conversion"},
		{bmdVideoOutputHardwareAnamorphicDownconversion,			"Hardware Anamorphic Down-conversion"},
		{bmdVideoOutputHardwareCenterCutDownconversion,				"Hardware Center Cut Down-conversion"},
		{bmdVideoOutputHardware720p1080pCrossconversion,			"Hardware 720p-1080p Cross-conversion"},
		{bmdVideoOutputHardwareAnamorphic720pUpconversion,			"Hardware Anamorphic 720p Upconversion"},
		{bmdVideoOutputHardwareAnamorphic1080iUpconversion,		"Hardware Anamorphic 1080i Upconversion"},
		{bmdVideoOutputHardwareAnamorphic149To720pUpconversion,	"Hardware Anamorphic 149 To 720p Upconversion"},
		{bmdVideoOutputHardwareAnamorphic149To1080iUpconversion,	"Hardware Anamorphic 149 To 1080iUpconversion"},
		{bmdVideoOutputHardwarePillarbox720pUpconversion,			"Hardware Pillar-box 720p Up-conversion"},
		{bmdVideoOutputHardwarePillarbox1080iUpconversion,			"Hardware Pillar-box 1080i Up-conversion"}
};

std::map<BMDIdleVideoOutputOperation, const char*> VideoOutputOpearationString =
{
		{bmdIdleVideoOutputBlack, 		"Black"},
		{bmdIdleVideoOutputLastFrame, "Last Frame"},
};

std::map<BMDDeckLinkCapturePassthroughMode, const char*> CapturePassThroughMode =
{
		{bmdDeckLinkCapturePassthroughModeDisabled,		"Disabled"},
		{bmdDeckLinkCapturePassthroughModeDirect,			"Direct"},
		{bmdDeckLinkCapturePassthroughModeCleanSwitch,	"Clean Switch"}
};

#endif /* SOURCE_CONST_H_ */
