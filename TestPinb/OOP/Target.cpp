/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Target.h"
#include "Pinball.h"
#include "PinballObject.h"
#include "Input.h"
#include "Timer.h"
#include "LedControl.h"

//-------------------------------------------------------//
Target::Target(uint8_t portNumberInput, uint8_t led) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Target Constructor"));
	#endif

	m_input = new Input(portNumberInput,this);
	m_hit = false;
	m_led = led;
	m_timerBlinkLed = new Timer(400, this, TimerType::continuous);
	m_timerBlinkLed->Disable();
}

//-------------------------------------------------------//
Target::~Target()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Target Destructor"));
	#endif
	
	/*
	delete m_timerBlinkLed;
	delete m_input;
	*/
}

//-------------------------------------------------------//
bool Target::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Target::Init"));
	#endif
	if (m_Pinball->GetStatus() == StatusPinball::playingmode)
	{
		m_timerBlinkLed->Start();
		m_hit = false;
	}
	return true;
}

//-------------------------------------------------------//
bool Target::NotifyEvent(Object *sender, uint8_t event, uint8_t value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Target::NotifyEvent"));
	#endif

	LedControl *ledControl = m_Pinball->GetLedControl();
	if (event == EVENT_EDGEPOSITIVE)
	{
		m_timerBlinkLed->Disable();
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_led);
		}
		m_hit = true;
		m_Pinball->NotifyEvent(this, event, value);
		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		if (m_Pinball->IsPlaying())
		{
			if (ledControl != NULL)
			{
				if (ledControl->IsTurn(m_led))
					ledControl->TurnOff(m_led);
				else
					ledControl->TurnOn(m_led);
			}
		}
		return true;
	}

	return false;
}
