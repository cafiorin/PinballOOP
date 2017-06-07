#ifndef PinballObject_h
#define PinballObject_h

#include "defines.h"

class PinballArduino;

class PinballObject
{
public:
	PinballObject(const char *szName, PinballArduino *pinball);
	char *getName() { return m_szName; }
	bool IsEnabled() { return m_enabled; }
	void LogMessage(const char *szMessage);
	void Debug(const char *szMessage);

//virtual methods	
	virtual bool Init();
	virtual bool Loop();

private:
	char m_szName[10];
	bool m_enabled;
	PinballArduino *m_pinball;
};

#endif
