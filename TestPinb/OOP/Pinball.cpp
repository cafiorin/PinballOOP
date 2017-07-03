/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "Pinball.h"
#include "PinballObject.h"
#include "HardwareSerial.h"
#include "Vector.h"

/*---------------------------------------------------------------------*/
Pinball::Pinball(const char *szName, HardwareSerial *serial, bool master)
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_master = master;
	m_serial = serial;
	
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Constructor");
	#endif
}

/*---------------------------------------------------------------------*/
Pinball::~Pinball()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Destructor");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		delete m_PinballObjs[i];
	}

}

/*---------------------------------------------------------------------*/
void Pinball::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	m_serial->println(szMessage);
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::AddPinballObject");
	#endif

	m_PinballObjs.push_back(Pinballobj);
}

/*---------------------------------------------------------------------*/
void Pinball::RemovePinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage("Pinball::RemovePinballObject");
#endif

	m_PinballObjs.pop_back(Pinballobj);
}


/*---------------------------------------------------------------------*/
void Pinball::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::Init");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Init();
	}
}


/*---------------------------------------------------------------------*/
void Pinball::Loop(int value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("Pinball::Loop");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		if (m_PinballObjs[i]->Loop(value))
		{
			#ifdef DEBUGMESSAGES
			char szMsg[50];
			sprintf(szMsg, "%s Loop return true", m_PinballObjs[i]->getName());
			LogMessage(szMsg);
			#endif
		}
	}
}
