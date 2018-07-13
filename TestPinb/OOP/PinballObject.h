/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballObject__INCLUDED_
#define PinballObject__INCLUDED_

#include "defines.h"

enum StatusPinball
{
	initializing,
	menusetup,
	menutest,
	attractmode,
	getplayers,
	playingmode,
	waitingmessages
};

class PinballMaster;

class PinballObject
{
public:
	PinballObject(const char *szName, PinballMaster *pinball);
	virtual ~PinballObject();
	char *getName() { return m_szName; }
	bool IsEnabled() { return m_enabled; }
	void Enable() { m_enabled = true; }
	void Disable() { m_enabled = false; }
	void DebugOut(const __FlashStringHelper *szMessage);
	void LogMessage(const char *szMessage);
    void LogMessageOut(const __FlashStringHelper *szMessage);
	void LogMessageValue(const char *szMessage, uint8_t value);
	void LogMessageValueOut(const __FlashStringHelper *szMessage, uint8_t value);
	void Debug(const char *szMessage);
	PinballMaster *GetPinball() { return m_pinball; }

//virtual methods
	virtual bool Init(StatusPinball status);
	virtual void Loop();
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);

protected:
	char m_szName[MAX_NAME];
	bool m_enabled;
	PinballMaster *m_pinball;
};

#endif
