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

private:
	IDeckLinkIterator				*m_deckLinkIterator;
	std::vector<IDeckLink*>		m_deckLinkDeviceList;
	std::vector<const char*>	m_deckLinkDeviceName;

	void ShowStatus(IDeckLinkStatus* deckLinkStatus, BMDDeckLinkStatusID statusID);
	const char* GetDisplayModeNameFromEnum(BMDDisplayMode displayModeEnum);
};





#endif /* DECKLINK_H_ */
