#include "decklink.h"

#include <iostream>
#include <mutex>

// Video mode parameters
const BMDDisplayMode      kDisplayMode = bmdModeHD1080i50;
const BMDVideoOutputFlags kOutputFlag  = bmdVideoOutputVANC;
const BMDPixelFormat      kPixelFormat = bmdFormat10BitYUV;

// Frame parameters
const uint32_t kFrameDuration = 1000;
const uint32_t kTimeScale = 25000;
const uint32_t kFrameWidth = 1920;
const uint32_t kFrameHeight = 1080;
const uint32_t kRowBytes = 5120;

// 10-bit YUV blue pixels
const uint32_t kBlueData[4] = { 0x40aa298, 0x2a8a62a8, 0x298aa040, 0x2a8102a8 };

// Studio Camera control packet:
// Set dynamic range to film.
// See Studio Camera manual for more information on protocol.
const uint8_t kSDIRemoteControlData[9] = { 0x00, 0x07, 0x00, 0x00, 0x01, 0x07, 0x01, 0x00, 0x00 };

// Data Identifier
const uint8_t kSDIRemoteControlDID = 0x51;

// Secondary Data Identifier
const uint8_t kSDIRemoteControlSDID = 0x53;

// Define VANC line for camera control
const uint32_t kSDIRemoteControlLine = 16;

// Keep track of the number of scheduled frames
uint32_t gTotalFramesScheduled = 0;

class OutputCallback: public IDeckLinkVideoOutputCallback
{
public:
	OutputCallback(IDeckLinkOutput* deckLinkOutput) : m_refCount(1)
	{
		m_deckLinkOutput = deckLinkOutput;
		m_deckLinkOutput->AddRef();
	}

	HRESULT	STDMETHODCALLTYPE ScheduledFrameCompleted(IDeckLinkVideoFrame* completedFrame, BMDOutputFrameCompletionResult result)
	{
		// When a video frame completes,reschedule another frame
		m_deckLinkOutput->ScheduleVideoFrame(completedFrame, gTotalFramesScheduled*kFrameDuration, kFrameDuration, kTimeScale);
		gTotalFramesScheduled++;
		return S_OK;
	}

	HRESULT	STDMETHODCALLTYPE ScheduledPlaybackHasStopped(void)
	{
		return S_OK;
	}
	// IUnknown needs only a dummy implementation
	HRESULT	STDMETHODCALLTYPE QueryInterface (REFIID iid, LPVOID *ppv)
	{
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{
		return AtomicIncrement(&m_refCount);
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		uint32_t newRefValue = AtomicDecrement(&m_refCount);

		if (newRefValue == 0)
			delete this;

		return newRefValue;
	}

private:
	IDeckLinkOutput*  m_deckLinkOutput;
	int32_t m_refCount;

	virtual ~OutputCallback(void)
	{
		m_deckLinkOutput->Release();
	}
};

class RemoteControlAncillaryPacket: public IDeckLinkAncillaryPacket
{
public:
	RemoteControlAncillaryPacket()
	{
		//MutexInit(&m_mutex);
		m_refCount = 1;
	}

	~RemoteControlAncillaryPacket()
	{
		//MutexDestroy(&m_mutex);
	}

	// IDeckLinkAncillaryPacket
	HRESULT STDMETHODCALLTYPE GetBytes(BMDAncillaryPacketFormat format, const void** data, uint32_t* size)
	{
		if (format != bmdAncillaryPacketFormatUInt8)
		{
			// In this example we only implement our packets with 8-bit data. This is fine because DeckLink accepts
			// whatever format we can supply and, if required, converts it.
			return E_NOTIMPL;
		}
		if (size) // Optional
			*size = (uint32_t)sizeof(kSDIRemoteControlData) / sizeof(*kSDIRemoteControlData);
		if (data) // Optional
			*data = (void*)kSDIRemoteControlData;
		return S_OK;
	}

	// IDeckLinkAncillaryPacket
	uint8_t STDMETHODCALLTYPE GetDID(void)
	{
		return kSDIRemoteControlDID;
	}

	// IDeckLinkAncillaryPacket
	uint8_t STDMETHODCALLTYPE GetSDID(void)
	{
		return kSDIRemoteControlSDID;
	}

	// IDeckLinkAncillaryPacket
	uint32_t STDMETHODCALLTYPE GetLineNumber(void)
	{
		// Returning zero here tells DeckLink to attempt to assume the line for known DIDs/SDIDs or otherwise place the
		// packet on the initial VANC lines of a frame. In this example we know the line for this mode, so let's use it.
		return kSDIRemoteControlLine;
	}

	// IDeckLinkAncillaryPacket
	uint8_t STDMETHODCALLTYPE GetDataStreamIndex(void)
	{
		return 0;
	}

	// IUnknown
	HRESULT	STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv)
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	// IUnknown
	ULONG STDMETHODCALLTYPE AddRef()
	{
		//MutexLock(&m_mutex);
		m_mutex.lock();
		m_refCount++;
		int32_t newRefValue = m_refCount;
		//MutexUnlock(&m_mutex);
		m_mutex.unlock();
		return newRefValue;
	}

	// IUnknown
	ULONG STDMETHODCALLTYPE Release()
	{
		//MutexLock(&m_mutex);
		m_mutex.lock();
		m_refCount--;
		int32_t newRefValue = m_refCount;
		//MutexUnlock(&m_mutex);
		m_mutex.unlock();

		if (newRefValue == 0)
			delete this;

		return newRefValue;
	}

private:
	int32_t m_refCount;
	//MUTEX m_mutex;
	std::mutex m_mutex;
};

IDeckLinkMutableVideoFrame* Decklink::CreateFrame(IDeckLinkOutput* deckLinkOutput)
{
	HRESULT											result;
	IDeckLinkMutableVideoFrame*				frame = NULL;
	IDeckLinkVideoFrameAncillaryPackets*	ancillaryPackets = NULL;
	IDeckLinkAncillaryPacket*					packet = NULL;

	result = deckLinkOutput->CreateVideoFrame(kFrameWidth, kFrameHeight, kRowBytes, kPixelFormat, bmdFrameFlagDefault, &frame);
	if (result != S_OK)
	{
		fprintf(stderr, "Could not create a video frame - result = %08x\n", result);
		goto fail;
	}

	FillBlue(frame);

	result = frame->QueryInterface(IID_IDeckLinkVideoFrameAncillaryPackets, (void**)&ancillaryPackets);
	if(result != S_OK)
	{
		fprintf(stderr, "Could not get frame's ancillary packet store - result = %08x\n", result);
		goto fail;
	}

	packet = new RemoteControlAncillaryPacket;
	result = ancillaryPackets->AttachPacket(packet);
	if (result != S_OK)
	{
		fprintf(stderr, "Could not attach packet to VANC - result = %08x\n", result);
		packet->Release(); // IDeckLinkVideoFrameAncillaryPackets didn't take ownership of the packet object
	}

fail:
	if (ancillaryPackets != NULL)
		ancillaryPackets->Release();
	return frame;
}

void Decklink::FillBlue(IDeckLinkMutableVideoFrame* theFrame)
{
	uint32_t* nextWord;
	uint32_t  wordsRemaining;

	theFrame->GetBytes((void**)&nextWord);
	wordsRemaining = (kRowBytes * kFrameHeight) / 4;

	while (wordsRemaining > 0)
	{
		*(nextWord++) = kBlueData[0];
		*(nextWord++) = kBlueData[1];
		*(nextWord++) = kBlueData[2];
		*(nextWord++) = kBlueData[3];
		wordsRemaining = wordsRemaining - 4;
	}
}

void Decklink::Display(uint32_t deviceId)
{
	HRESULT 						result;
	IDeckLinkOutput*			deckLinkOutput   = NULL;
	OutputCallback*			outputCallback   = NULL;
	IDeckLinkVideoFrame*    videoFrameBlue   = NULL;

	if (deviceId<m_deckLinkDeviceList.size())
	{
		std::cout << "Device " << deviceId << ": " << m_deckLinkDeviceDisplayName[deviceId] << std::endl;

		// Obtain the output interface for the DeckLink device
		result = m_deckLinkDeviceList[deviceId]->QueryInterface(IID_IDeckLinkOutput, (void**)&deckLinkOutput);
		if(result != S_OK)
		{
			fprintf(stderr, "Could not obtain the IDeckLinkInput interface - result = %08x\n", result);
			goto fail;
		}

		// Create an instance of output callback
		outputCallback = new OutputCallback(deckLinkOutput);
		if(outputCallback == NULL)
		{
			fprintf(stderr, "Could not create output callback object\n");
			goto fail;
		}

		// Set the callback object to the DeckLink device's output interface
		result = deckLinkOutput->SetScheduledFrameCompletionCallback(outputCallback);
		if(result != S_OK)
		{
			fprintf(stderr, "Could not set callback - result = %08x\n", result);
			goto fail;
		}

		// Enable video output
		result = deckLinkOutput->EnableVideoOutput(kDisplayMode, kOutputFlag);
		if(result != S_OK)
		{
			fprintf(stderr, "Could not enable video output - result = %08x\n", result);
			goto fail;
		}

		// Create a frame with defined format
		videoFrameBlue = CreateFrame(deckLinkOutput);

		// Schedule a blue frame 3 times
		for(int i = 0; i < 3; i++)
		{
			result = deckLinkOutput->ScheduleVideoFrame(videoFrameBlue, gTotalFramesScheduled*kFrameDuration, kFrameDuration, kTimeScale);
			if(result != S_OK)
			{
				fprintf(stderr, "Could not schedule video frame - result = %08x\n", result);
				goto fail;
			}
			gTotalFramesScheduled ++;
		}

		// Start
		result = deckLinkOutput->StartScheduledPlayback(0, kTimeScale, 1.0);
		if(result != S_OK)
		{
			fprintf(stderr, "Could not start - result = %08x\n", result);
			goto fail;
		}

		// Wait until user presses Enter
		printf("Monitoring... Press <RETURN> to exit\n");

		getchar();

		printf("Exiting.\n");

		// Stop capture
		result = deckLinkOutput->StopScheduledPlayback(0, NULL, 0);

		// Disable the video input interface
		result = deckLinkOutput->DisableVideoOutput();

fail:
		// Release resources
		SAEF_RELEASE(deckLinkOutput);
		SAEF_RELEASE(videoFrameBlue);
		SAEF_RELEASE(outputCallback);
	}
}
