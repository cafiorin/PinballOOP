/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballObject_h
#define PinballObject_h

#include "defines.h"

class Pinball;

class PinballObject
{
public:
	PinballObject(const char *szName, Pinball *pinball);
	virtual ~PinballObject();
	char *getName() { return m_szName; }
	bool IsEnabled() { return m_enabled; }
	void LogMessage(const char *szMessage);
	void Debug(const char *szMessage);

//virtual methods	
	virtual bool Init();
	virtual bool Loop(int value);

private:
	char m_szName[10];
	bool m_enabled;
	Pinball *m_pinball;
};

#endif
