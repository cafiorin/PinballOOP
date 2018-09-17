/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Output.h"
#include "Pinball.h"
#include "Multiplex.h"
#include "Event.h"

//-------------------------------------------------------//
Output::Output(uint8_t port):Port(port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Output Constructor"));
	#endif

	m_Multiplex = m_Pinball->GetMultiplex();
	m_TimerOn = new Timer(100, this,TimerType::once);
	m_Pinball->AddPinballOutput(this);

	//Init();
}

//-------------------------------------------------------//
Output::~Output()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Output Destructor"));
	#endif

	delete m_TimerOn;
}

//-------------------------------------------------------//
bool Output::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Output::Init"));
	#endif

	TurnOff();
	return true;
}

//-------------------------------------------------------//
void Output::TurnOn()
//-------------------------------------------------------//
{
	if(m_Enabled)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("Output::TurnOn"));
		#endif

		m_turnOn = true;
		if (m_Multiplex != NULL)
		{
			m_Multiplex->writeChannel(m_portNumber, HIGH);
		}
	}
}

//-------------------------------------------------------//
void Output::TurnOnByTimer(long time)
//-------------------------------------------------------//
{
	if (m_Enabled)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("Output::TurnOnByTime"));
		#endif

		m_timerDelay = time;
		m_TimerOn->Start();
		TurnOn();
	}
}

//-------------------------------------------------------//
bool Output::NotifyEvent(Object *sender, Event *event)
//-------------------------------------------------------//
{
    #ifdef DEBUGMESSAGES
    LogMessage(F("Output::NotifyEvent"));
    #endif

	if (event->GetIdEvent() == EVENT_TIMEISOVER)
	{
		TurnOff();
		return true;
	}

	return false;
}

//-------------------------------------------------------//
void Output::TurnOff()
//-------------------------------------------------------//
{
	if(m_Enabled)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("Output::TurnOff"));
		#endif

		m_timerDelay = 0;
		m_turnOn = false;

		if (m_Multiplex != NULL)
		{
			m_Multiplex->writeChannel(m_portNumber, LOW);
		}
	}
}
