/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PinballObject.h"
#include "Pinball.h"

/*---------------------------------------------------------------------*/
PinballObject::PinballObject(const char *szName, Pinball *pinball)
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_enabled = true;
	m_pinball = pinball;

	if (m_pinball != NULL && m_pinball != this)
	{
		#ifdef DEBUGMESSAGES
		Debug("PinballObject Constructor");
		#endif

		m_pinball->AddPinballObject(this);
	}
}

/*---------------------------------------------------------------------*/
PinballObject::~PinballObject()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("PinballObject Destructor");
	#endif

	if (m_pinball != NULL && m_pinball != this)
		m_pinball->RemovePinballObject(this);
}


/*---------------------------------------------------------------------*/
void PinballObject::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	if (strlen(szMessage) + strlen(m_szName) + 1 < 50)
	{
		char szMsg[50];
		sprintf(szMsg, "[%s]:%s", m_szName, szMessage);

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
bool PinballObject::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("PinballObject::Init");
	#endif

	return true;
}

/*---------------------------------------------------------------------*/
bool PinballObject::Loop(int value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("PinballObject::Loop");
	#endif

	return false;
}

//---------------------------------------------------------------------//
bool PinballObject::NotifyEvent(int id, int event)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("PinballObject::NotifyEvent");
	#endif

	return false;
}
