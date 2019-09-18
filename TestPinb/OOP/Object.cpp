/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Object.h"
#include "PinballMaster.h"
#include "HardwareSerial.h"

//Statics init
#ifdef DEBUGMESSAGES
uint8_t Object::m_Ids = 0;
#endif // DEBUGMESSAGES


HardwareSerial *Object::m_Serial = NULL;
Pinball *Object::m_Pinball = NULL;

//-------------------------------------------------------//
Object::Object()  
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	m_Id = m_Ids++;
#endif
}

#ifdef DEBUGMESSAGES
//-------------------------------------------------------//
void Object::LogMessage(const __FlashStringHelper *szMessage)
//-------------------------------------------------------//
{
	if (m_Serial != NULL)
	{
		m_Serial->print(m_Id);
		m_Serial->print(F(" : "));
		m_Serial->println(szMessage);
		m_Serial->flush();
	}
}

//-------------------------------------------------------//
void Object::LogMessageToConstChar(const char *szMessage)
//-------------------------------------------------------//
{
	if (m_Serial != NULL)
	{
		m_Serial->print(m_Id);
		m_Serial->print(F(" : "));
		m_Serial->println(szMessage);
		m_Serial->flush();
	}
}

#endif


//---------------------------------------------------------------------//
bool Object::NotifyEvent(Object * /*sender*/, uint8_t /*event*/, uint8_t value)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Object::NotifyEvent"));
	#endif

	return false;
}


