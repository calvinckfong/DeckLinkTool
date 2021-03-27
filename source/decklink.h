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

#define SAEF_RELEASE(x)	if (x) x->Release();

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

class NotificationCallback: public IDeckLinkInputCallback
{
public:
	IDeckLinkInput* m_deckLinkInput;

	NotificationCallback(IDeckLinkInput *deckLinkInput);

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
	int32_t		m_refCount;

	virtual ~NotificationCallback() {}
};



#endif /* DECKLINK_H_ */
