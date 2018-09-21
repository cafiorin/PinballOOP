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
#include "Event.h"
#include "Pinball.h"

//-------------------------------------------------------//
Bumper::Bumper(uint8_t portNumberInput, uint8_t portNumberOutput,uint8_t LedNumber) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Bumper Constructor"));
	#endif

	m_input = new Input(portNumberInput,this);
	m_output = new Output(portNumberOutput);
	m_Led = LedNumber;
	m_TimerLed = new Timer(200, this, TimerType::once);
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
	delete m_TimerLed;
	*/
}

//-------------------------------------------------------//
bool Bumper::NotifyEvent(Object *sender, Event *event)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Bumper::NotifyEvent"));
	#endif

	LedControl *pLedControl = m_Pinball->GetLedControl();
	if (event->GetIdEvent() == EVENT_EDGEPOSITIVE)
	{
		m_output->TurnOnByTimer(TIME_COIL_ON);
		m_Pinball->NotifyEvent(sender, event);
		if (pLedControl != NULL)
		{
			pLedControl->TurnOn(m_Led);
		}
		m_TimerLed->Start();
		return true;
	}
	else if (event->GetIdEvent() == EVENT_TIMEISOVER)
	{
		if (pLedControl != NULL)
		{
			pLedControl->TurnOff(m_Led);
		}
	}
	return false;
}

