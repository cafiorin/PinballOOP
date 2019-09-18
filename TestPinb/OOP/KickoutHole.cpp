/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "KickoutHole.h"
#include "Pinball.h"
#include "PinballObject.h"

//-------------------------------------------------------//
KickoutHole::KickoutHole(uint8_t portNumberInput, uint8_t portNumberOutput) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("KickoutHole Constructor"));
	#endif

	
	m_input = new Input(portNumberInput,this);
	m_output = new Output(portNumberOutput);
	
}

//-------------------------------------------------------//
KickoutHole::~KickoutHole()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("KickoutHole Destructor"));
	#endif
	
	/*
	delete m_input;
	delete m_output;
	*/
}

//-------------------------------------------------------//
bool KickoutHole::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("KickoutHole::Init"));
	#endif

	LanchBall();
	return true;
}

//-------------------------------------------------------//
bool KickoutHole::NotifyEvent(Object * /*sender*/, uint8_t event, uint8_t value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("KickoutHole::NotifyEvent"));
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_Pinball->NotifyEvent(this, event, value);
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

	if (m_input->GetInput())
	{
		m_output->TurnOnByTimer(TIME_COIL_ON);
	}
}