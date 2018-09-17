/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "KickoutHole.h"
#include "Pinball.h"
#include "Event.h"
#include "PinballObject.h"

//-------------------------------------------------------//
KickoutHole::KickoutHole(uint8_t portNumberInput, uint8_t portNumberOutput) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("KickoutHole Constructor"));
	#endif

	m_input1 = new Input(portNumberInput,this);
	m_output = new Output(portNumberOutput);
}

//-------------------------------------------------------//
KickoutHole::~KickoutHole()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("KickoutHole Destructor"));
	#endif
	
	delete m_input1;
	delete m_output;
}

//-------------------------------------------------------//
bool KickoutHole::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("KickoutHole::Init"));
	#endif

	m_ball = false;
	if (m_input1->GetInput())
	{
		m_output->TurnOnByTimer();
	}

	return true;
}

//-------------------------------------------------------//
bool KickoutHole::NotifyEvent(Object *sender, Event *event)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("KickoutHole::NotifyEvent"));
	#endif

	if (event->GetIdEvent() == EVENT_EDGEPOSITIVE)
	{
		m_ball = true;
		m_Pinball->NotifyEvent(this, event);
		return true;
	}
	return false;
}


//-------------------------------------------------------//
void KickoutHole::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("KickoutHole::LanchBall"));
	#endif

	if (m_ball)
	{
		m_ball = false;
		m_output->TurnOnByTimer(TIME_COIL_ON);
	}
}