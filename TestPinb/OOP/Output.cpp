/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Output.h"
#include "PinballMaster.h"
#include "Multiplex.h"

//-------------------------------------------------------//
Output::Output(const char *szName, PinballMaster *pinball, uint8_t port):Port(pinball,szName, port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Output Constructor");
	#endif

	m_Multiplex = pinball->GetMultiplex();
	m_TimerOn = new Timer(100, "TOon", pinball,this,TimerType::once);
	pinball->AddPinballOutput(this);

	//Init();
}

//-------------------------------------------------------//
Output::~Output()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Output Destructor");
	#endif

	delete m_TimerOn;
}

//-------------------------------------------------------//
bool Output::Init(StatusPinball status)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output::Init");
	#endif

	TurnOff();
	return true;
}

//-------------------------------------------------------//
void Output::TurnOn()
//-------------------------------------------------------//
{
	if(m_enabled)
	{
		#ifdef DEBUGMESSAGES
		Debug("Output::TurnOn");
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
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGES
		Debug("Output::TurnOnByTime");
		#endif

		m_timerDelay = time;
		m_TimerOn->Start();
		TurnOn();
	}
}

//-------------------------------------------------------//
bool Output::NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend)
//-------------------------------------------------------//
{
    #ifdef DEBUGMESSAGES
    Debug("Output::NotifyEvent");
    #endif

	if (event == EVENT_TIMEISOVER)
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
	if(m_enabled)
	{
		#ifdef DEBUGMESSAGES
		Debug("Output::TurnOff");
		#endif

		m_timerDelay = 0;
		m_turnOn = false;

		if (m_Multiplex != NULL)
		{
			m_Multiplex->writeChannel(m_portNumber, LOW);
		}
	}
}
