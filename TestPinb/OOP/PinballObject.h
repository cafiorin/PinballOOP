/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballObject__INCLUDED_
#define PinballObject__INCLUDED_

#include "defines.h"

class Pinball;

class PinballObject
{
public:
	PinballObject(const char *szName, Pinball *pinball);
	virtual ~PinballObject();
	char *getName() { return m_szName; }
	bool IsEnabled() { return m_enabled; }
	bool IsRemoteObject() { return m_remote; }
	void Enable() { m_enabled = true; }
	void Disable() { m_enabled = false; }
	void LogMessage(const char *szMessage);
	void Debug(const char *szMessage);
	Pinball *GetPinball() { return m_pinball; }

//virtual methods	
	virtual bool Init();
	virtual bool Loop(int value);

protected:
	char m_szName[10];
	bool m_enabled;
	bool m_remote;
	Pinball *m_pinball;
};

#endif
