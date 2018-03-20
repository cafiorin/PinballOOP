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
	strcpy(m_szName, szName);
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
	Debug("PinballObject Destructor");
	#endif

	if (m_pinball != NULL)
		m_pinball->RemovePinballObject(this);
}


/*---------------------------------------------------------------------*/
void PinballObject::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	if (strlen(szMessage) + strlen(m_szName) < MAX_SIZE_DEBUG_MESSAGE)
	{
		char szMsg[MAX_SIZE_DEBUG_MESSAGE];
		sprintf(szMsg, "[%s]:%s", m_szName, szMessage);

		if (m_pinball != NULL)
			m_pinball->LogMessage(szMsg);
	}
}

/*---------------------------------------------------------------------*/
void PinballObject::LogMessageValue(const char *szMessage,int value)
/*---------------------------------------------------------------------*/
{
	if (strlen(szMessage) + strlen(m_szName)+10 < MAX_SIZE_DEBUG_MESSAGE)
	{
		char szMsg[MAX_SIZE_DEBUG_MESSAGE];
		sprintf(szMsg, "[%s]:%s-value:%d", m_szName, szMessage,value);

		if (m_pinball != NULL)
			m_pinball->LogMessage(szMsg);
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
bool PinballObject::Init(StatusPinball status)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("PinballObject::Init");
	#endif

	return true;
}

/*---------------------------------------------------------------------*/
void PinballObject::Loop()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("PinballObject::Loop");
	#endif
}

//---------------------------------------------------------------------//
bool PinballObject::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("PinballObject::NotifyEvent");
	#endif

	return false;
}
