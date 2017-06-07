#include "PinballArduino.h"
#include "PinballObject.h"
#include "HardwareSerial.h"
#include "Vector.h"

/*---------------------------------------------------------------------*/
PinballArduino::PinballArduino(const char *szName, HardwareSerial *serial, bool master)
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_master = master;
	m_serial = serial;
}

/*---------------------------------------------------------------------*/
void PinballArduino::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	m_serial->println(szMessage);
	#endif
}

/*---------------------------------------------------------------------*/
void PinballArduino::AddPinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
	m_PinballObjs.push_back(Pinballobj);
}

/*---------------------------------------------------------------------*/
void PinballArduino::Init()
/*---------------------------------------------------------------------*/
{
	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Init();
	}
}


/*---------------------------------------------------------------------*/
void PinballArduino::Loop()
/*---------------------------------------------------------------------*/
{
	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Loop();
	}
}
