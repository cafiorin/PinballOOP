/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Pinball__INCLUDED_
#define Pinball__INCLUDED_

#include "defines.h"
#include "Vector.h"

class PinballObject;
class HardwareSerial;

class Pinball
{
public:
	Pinball(const char *szName, HardwareSerial *serial, bool master=false);
	virtual ~Pinball();
	char *getName() { return m_szName; }
	bool IsMaster() { return m_master; }
	void LogMessage(const char *szMessage);
	void AddPinballObject(PinballObject *Pinballobj);
	void RemovePinballObject(PinballObject *Pinballobj);
	void Init();
	void Loop(int value);

private:
	char m_szName[10];
	bool m_master;
	HardwareSerial *m_serial;
	Vector<PinballObject *> m_PinballObjs;
};

#endif
