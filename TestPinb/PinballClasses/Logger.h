#ifndef Logger_h
#define Logger_h

#include "HardwareSerial.h"


class Logger
{
public: 
	Logger(HardwareSerial* serial)
	{
		m_Serial = serial;
	}

#ifdef DEBUGMESSAGES
	static void LogMessage(const __FlashStringHelper* szMessage)
	{
		if (m_Serial != NULL)
		{
			m_Serial->println(szMessage);
			m_Serial->flush();
		}
	}

	static void LogMessageToConstChar(const char* szMessage)
	{
		if (m_Serial != NULL)
		{
			m_Serial->println(szMessage);
			m_Serial->flush();
		}
	}
	
	static void LogMessageByte(byte value)
	{
		if (m_Serial != NULL)
		{
			m_Serial->println(value);
			m_Serial->flush();
		}
	}

#endif

private:
	static HardwareSerial* m_Serial;


};

#endif