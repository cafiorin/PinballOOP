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

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_timerBlinkLed->Disable();
		m_pinball->GetLedControl()->TurnOn(m_led);
		m_hit = true;
		m_pinball->NotifyEvent(this, event, valueToSend);
		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		if (m_pinball->IsPlaying())
		{
			if (m_pinball->GetLedControl()->IsTurn(m_led))
				m_pinball->GetLedControl()->TurnOff(m_led);
			else
				m_pinball->GetLedControl()->TurnOn(m_led);
		}
		return true;
	}

	return false;
}
