/*
 * decklink.h
 *
 *  Created on: Mar 25, 2021
 *      Author: calvin.fong
 */

#ifndef DECKLINK_H_
#define DECKLINK_H_

#include "DeckLinkAPI.h"
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define NumBufferedFrameCount 4
#define SAEF_RELEASE(x)	if (x) x->Release();

typedef struct FrameInfo_t
{
	int32_t width, height;
	BMDPixelFormat pix_fmt;
	BMDFrameFlags flags;
};

class Decklink
{
public:
	Decklink();
	~Decklink();

	bool Init();
	void ListDevices();
	void ListDeviceProfile(uint32_t deviceId);
	void ListDeviceDisplayMode(uint32_t deviceId);
	void ListDeviceConfig(uint32_t deviceId);
	void ListDeviceStatus(uint32_t deviceId);

	void Capture(uint32_t deviceId);
	void Display(uint32_t deviceId);

private:
	IDeckLinkIterator				*m_deckLinkIterator;
	std::vector<IDeckLink*>		m_deckLinkDeviceList;
	std::vector<const char*>	m_deckLinkDeviceModelName;
	std::vector<const char*>	m_deckLinkDeviceDisplayName;

	void ShowAttribute(IDeckLinkProfileAttributes* deckLinkAttributes, BMDDeckLinkAttributeID attributeID);
	void ShowConfig(IDeckLinkConfiguration* deckLinkConfiguration, BMDDeckLinkConfigurationID configID);
	void ShowStatus(IDeckLinkStatus* deckLinkStatus, BMDDeckLinkStatusID statusID);
};

class NotificationDisplayCallback;
class OutputCallback;

class DeckLinkDevice
{
public:
	DeckLinkDevice();
	~DeckLinkDevice();

	HRESULT setup(IDeckLink* deckLink);
	HRESULT waitForReferenceLock();
	void notifyReferenceInputChanged();
	HRESULT prepareForPlayback();
	HRESULT startPlayback();
	HRESULT stopPlayback();
	HRESULT waitForPlaybackStop();
	void notifyDeviceStopped();
	bool stopped() const;
	HRESULT cleanUpFromPlayback();
	HRESULT scheduleNextFrame();

private:
	IDeckLink*								m_deckLink;
	IDeckLinkConfiguration*				m_deckLinkConfig;
	IDeckLinkStatus*						m_deckLinkStatus;
	IDeckLinkNotification*				m_deckLinkNotification;
	NotificationDisplayCallback*		m_notificationCallback;
	IDeckLinkOutput*						m_deckLinkOutput;
	OutputCallback*						m_outputCallback;
	std::array<IDeckLinkVideoFrame*, NumBufferedFrameCount>	m_frames;
	uint32_t									m_totalFramesScheduled;
	uint32_t									m_nextFrameToSchedule;
	std::mutex								m_mutex;
	bool										m_stopped;
	std::condition_variable				m_stopCondition;
	std::condition_variable				m_referenceCondition;
};

class NotificationCaptureCallback: public IDeckLinkInputCallback
{
public:
	IDeckLinkInput* m_deckLinkInput;

	NotificationCaptureCallback(IDeckLinkInput *deckLinkInput);

	HRESULT	STDMETHODCALLTYPE QueryInterface (REFIID iid, LPVOID *ppv);
	ULONG		STDMETHODCALLTYPE AddRef();
	ULONG		STDMETHODCALLTYPE Release();
	HRESULT	STDMETHODCALLTYPE VideoInputFormatChanged(
			/* in */ BMDVideoInputFormatChangedEvents notificationEvents,
			/* in */ IDeckLinkDisplayMode *newDisplayMode,
			/* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags);
	HRESULT	STDMETHODCALLTYPE VideoInputFrameArrived(
			/* in */ IDeckLinkVideoInputFrame* videoFrame,
			/* in */ IDeckLinkAudioInputPacket* audioPacket);

private:
	int32_t			m_refCount;
	FrameInfo_t		m_lastFrameInfo;

	virtual ~NotificationCaptureCallback() {}
};

class OutputCallback: public IDeckLinkVideoOutputCallback
{
public:
	OutputCallback(DeckLinkDevice* deckLinkDevice);

	HRESULT	STDMETHODCALLTYPE ScheduledFrameCompleted(IDeckLinkVideoFrame* completedFrame, BMDOutputFrameCompletionResult result) override;
	HRESULT	STDMETHODCALLTYPE ScheduledPlaybackHasStopped(void) override;
	HRESULT	STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv) override;
	ULONG		STDMETHODCALLTYPE AddRef() override;
	ULONG		STDMETHODCALLTYPE Release() override;

private:
	DeckLinkDevice*  m_deckLinkDevice;
	std::atomic<int32_t> m_refCount;
};

class NotificationDisplayCallback: public IDeckLinkVideoOutputCallback
{
public:
	NotificationDisplayCallback(DeckLinkDevice* deckLinkDevice);

	HRESULT	STDMETHODCALLTYPE Notify(BMDNotifications topic, uint64_t param1, uint64_t param2);
	HRESULT	STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv) override;
	ULONG		STDMETHODCALLTYPE AddRef() override;
	ULONG		STDMETHODCALLTYPE Release() override;

private:
	DeckLinkDevice		*m_deckLinkDevice;
	int32_t				m_refCount;
};

#endif /* DECKLINK_H_ */
