/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PinballObject.h"
#include "PinballMaster.h"

/*---------------------------------------------------------------------*/
PinballObject::PinballObject(const char *szName, PinballMaster *pinball)
/*---------------------------------------------------------------------*/
{
	if(strlen(szName)<MAX_NAME)
		strcpy(m_szName, szName);
	else
		strcpy(m_szName, "MAX_NAME");

	m_enabled = true;
	m_pinball = pinball;

	if (m_pinball != NULL)
	{
		m_pinball->AddPinballObject(this);
	}
}

/*---------------------------------------------------------------------*/
PinballObject::~PinballObject()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	DebugOut(F("PinballObject Destructor"));
	#endif

	if (m_pinball != NULL)
		m_pinball->RemovePinballObject(this);
}


/*---------------------------------------------------------------------*/
void PinballObject::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	if (strlen(szMessage) + strlen(m_szName)+5 < MAX_SIZE_DEBUG_MESSAGE)
	{
		char szMsg[MAX_SIZE_DEBUG_MESSAGE];
		sprintf(szMsg, "[%s]:%s", m_szName, szMessage);

		if (m_pinball != NULL)
			m_pinball->LogMessage(szMsg);
	}
}

/*---------------------------------------------------------------------*/
void PinballObject::LogMessageOut(const __FlashStringHelper *szMessage)
/*---------------------------------------------------------------------*/
{
	if (m_pinball != NULL && m_pinball->GetSerial() != NULL)
	{
		m_pinball->GetSerial()->print(m_szName);
		m_pinball->GetSerial()->print(F(":"));
		m_pinball->GetSerial()->println(szMessage);
		m_pinball->GetSerial()->flush();
		delay(100);
	}

}

/*---------------------------------------------------------------------*/
void PinballObject::LogMessageValue(const char *szMessage,uint8_t value)
/*---------------------------------------------------------------------*/
{
	if (strlen(szMessage) + strlen(m_szName)+16 < MAX_SIZE_DEBUG_MESSAGE)
	{
		char szMsg[MAX_SIZE_DEBUG_MESSAGE];
		sprintf(szMsg, "[%s]:%s-value:%d", m_szName, szMessage,value);

		if (m_pinball != NULL)
			m_pinball->LogMessage(szMsg);
	}
}

/*---------------------------------------------------------------------*/
void PinballObject::LogMessageValueOut(const __FlashStringHelper *szMessage,uint8_t value)
/*---------------------------------------------------------------------*/
{
	if (m_pinball != NULL && m_pinball->GetSerial() != NULL)
	{
		m_pinball->GetSerial()->print(m_szName);
		m_pinball->GetSerial()->print(F(":"));
		m_pinball->GetSerial()->print(szMessage);
		m_pinball->GetSerial()->print(F(":"));
		m_pinball->GetSerial()->println(value);
		m_pinball->GetSerial()->flush();
		delay(100);
	}

}

/*---------------------------------------------------------------------*/
void PinballObject::Debug(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage(szMessage);
	#endif // DEBUGMESSAGES
}

/*---------------------------------------------------------------------*/
void PinballObject::DebugOut(const __FlashStringHelper *szMessage)
/*---------------------------------------------------------------------*/
{
	if (m_pinball != NULL && m_pinball->GetSerial() != NULL)
	{
		m_pinball->GetSerial()->println(szMessage);
		m_pinball->GetSerial()->flush();
		delay(100);
	}
}
/*---------------------------------------------------------------------*/
bool PinballObject::Init(StatusPinball status)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	DebugOut(F("PinballObject::Init"));
	#endif

	return true;
}

/*---------------------------------------------------------------------*/
void PinballObject::Loop()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	DebugOut(F("PinballObject::Loop"));
	#endif
}

//---------------------------------------------------------------------//
bool PinballObject::NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	DebugOut(F("PinballObject::NotifyEvent"));
	#endif

	return false;
}
