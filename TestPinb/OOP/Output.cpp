/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Output.h"
#include "Pinball.h"
#include "Multiplex.h"

//-------------------------------------------------------//
Output::Output(const char *szName, Pinball *pinball, int port, Multiplex *multiplex ):Port(pinball,szName, port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output Constructor");
	#endif
	m_portNumber = port;
	m_TimerOn = new Timer(100, "TOon", pinball);
	m_Multiplex = multiplex;

	pinball->AddPinballOutput(this);

	Init();
}

//-------------------------------------------------------//
Output::~Output()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output Destructor");
	#endif
}

//-------------------------------------------------------//
bool Output::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output::Init");
	#endif

	#ifdef ARDUINOLIB
    pinMode(m_portNumber, OUTPUT);
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

		m_Multiplex->writeChannel(m_portNumber, HIGH);
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
		m_TimerOn->Init();
		TurnOn();
	}
}

//-------------------------------------------------------//
bool Output::Loop(int value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Output::Loop");
	#endif

	if (m_enabled && m_timerDelay > 0)
	{
		if (m_TimerOn->Check(m_timerDelay))
		{
			#ifdef DEBUGMESSAGES
			Debug("Output::Timeout !");
			#endif

			TurnOff();
			return true;
		}
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

		m_Multiplex->writeChannel(m_portNumber, LOW);
	}
}
