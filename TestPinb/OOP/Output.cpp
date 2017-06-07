/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Output.h"


//-------------------------------------------------------//
Output::Output(const char *szName, Pinball *pinball, int port):Port(pinball,szName, port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output Constructor");
	#endif
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

	#ifdef ARDUINO
    pinMode(m_portNumber, OUTPUT);
	#endif

	TurnOff();

	return true;
}

//-------------------------------------------------------//
void Output::TurnOn()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output::TurnOn");
	#endif

	if(m_enabled)
	{
		m_turnOn = true;

		#ifdef ARDUINO
		digitalWrite(m_portNumber, HIGH);
		#endif
	}
}

//-------------------------------------------------------//
void Output::TurnOff()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output::TurnOff");
	#endif

	if(m_enabled)
	{
		m_turnOn = false;

		#ifdef ARDUINO
		digitalWrite(m_portNumber, LOW);
		#endif
	}
}
