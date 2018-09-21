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
int Object::m_Ids = 0;
HardwareSerial *Object::m_Serial = NULL;
Pinball *Object::m_Pinball = NULL;

//-------------------------------------------------------//
Object::Object()  
//-------------------------------------------------------//
{
	m_Id = m_Ids++;
}

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

//---------------------------------------------------------------------//
bool Object::NotifyEvent(Object *sender, uint8_t event, uint8_t value)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Object::NotifyEvent"));
	#endif

	return false;
}


