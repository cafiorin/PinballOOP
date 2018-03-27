/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Target.h"
#include "PinballMaster.h"
#include "PinballObject.h"
#include "Input.h"
#include "Timer.h"

//-------------------------------------------------------//
Target::Target(const char *szName, PinballMaster *pinball, int portNumberInput, int led) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Target Constructor");
	#endif

	m_input = new Input("TIn", pinball, portNumberInput,this);
	m_hit = false;
	m_led = led;
	m_timerBlinkLed = new Timer(400, "TTLB", pinball, this, TimerType::continuous);
	m_timerBlinkLed->Disable();
}

//-------------------------------------------------------//
Target::~Target()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Target Destructor");
	#endif
	
	delete m_timerBlinkLed;
	delete m_input;
}

//-------------------------------------------------------//
bool Target::Init(StatusPinball status)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Target::Init");
	#endif
	if (status == StatusPinball::playingmode)
	{
		m_timerBlinkLed->Start();
		m_hit = false;
	}
	return true;
}

//-------------------------------------------------------//
bool Target::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Target::NotifyEvent");
	#endif

	LedControl *ledControl = m_pinball->GetLedControl();
	if (event == EVENT_EDGEPOSITIVE)
	{
		m_timerBlinkLed->Disable();
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_led);
		}
		m_hit = true;
		m_pinball->NotifyEvent(this, event, valueToSend);
		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		if (m_pinball->IsPlaying())
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
