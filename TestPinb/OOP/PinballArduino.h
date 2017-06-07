#ifndef PinballArduino_h
#define PinballArduino_h

#include "defines.h"
#include "Vector.h"

class PinballObject;
class HardwareSerial;

class PinballArduino
{
public:
	PinballArduino(const char *szName, HardwareSerial *serial, bool master=false);
	char *getName() { return m_szName; }
	bool IsMaster() { return m_master; }
	void LogMessage(const char *szMessage);
	void AddPinballObject(PinballObject *Pinballobj);
	void Init();
	void Loop();

private:
	char m_szName[10];
	bool m_master;
	HardwareSerial *m_serial;
	Vector<PinballObject *> m_PinballObjs;
};

#endif
