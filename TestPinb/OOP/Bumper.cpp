/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Bumper.h"
#include "Input.h"
#include "Output.h"
#include "LedControl.h"
#include "PinballObject.h"
#include "Pinball.h"

//-------------------------------------------------------//
Bumper::Bumper(uint8_t portNumberInput, uint8_t portNumberOutput,uint8_t portLed) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Bumper Constructor"));
	#endif

	m_input = new Input(portNumberInput,this);
	m_output = new Output(portNumberOutput);
	m_Led = new Output(portLed);
}

//-------------------------------------------------------//
Bumper::~Bumper()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Bumper Destructor"));
	#endif

	/*
	delete m_input;
	delete m_output;
	delete m_Led;
	delete m_TimerLed;
	*/
}

//-------------------------------------------------------//
bool Bumper::NotifyEvent(Object *sender, uint8_t event, uint8_t value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Bumper::NotifyEvent"));
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_output->Pulse();
		m_Pinball->NotifyEvent(sender, event, value);
		m_Led->TurnOnByTimer(500);
		return true;
	}
	return false;
}

