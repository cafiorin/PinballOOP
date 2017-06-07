#include "PinballObject.h"
#include "PinballArduino.h"

/*---------------------------------------------------------------------*/
PinballObject::PinballObject(const char *szName, PinballArduino *pinball)
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_enabled = true;
	m_pinball = pinball;
	
	if(m_pinball != NULL)
		m_pinball->AddPinballObject(this);

	Init();
}

/*---------------------------------------------------------------------*/
void PinballObject::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	char szMsg[30];
	sprintf(szMsg, "[%s]:%s\n", m_szName, szMessage);
	
	if (m_pinball != NULL)
		m_pinball->LogMessage(szMsg);
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
	Debug("Init");
	#endif

	return true;
}

/*---------------------------------------------------------------------*/
bool PinballObject::Loop()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("Loop");
	#endif

	return false;
}

