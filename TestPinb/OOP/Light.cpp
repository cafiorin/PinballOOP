/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Light.h"
#include "Event.h"

//-------------------------------------------------------//
Light::Light(uint8_t port):Output(port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Light Constructor"));
	#endif

	m_timerBlinking = new Timer(700, this,TimerType::continuous);
}

//-------------------------------------------------------//
Light::~Light()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Light Destructor"));
	#endif

	delete m_timerBlinking;
}

//-------------------------------------------------------//
bool Light::NotifyEvent(Object *sender, Event *event)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Light::NotifyEvent"));
	#endif

	if (event->GetIdEvent() == EVENT_TIMEISOVER)
	{
		if (this->IsTurnOn())
			TurnOff();
		else
			TurnOn();
		return true;
	}

	return false;
}

//-----------------------------------------------------//
void Light::StartBlink(long value)
//-----------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Output::StartBlink"));
	#endif

	m_timerBlinking->ChangeValue(value);
}

//-----------------------------------------------------//
void Light::EndBlink()
//-----------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Output::EndBlink"));
	#endif

	m_timerBlinking->Disable();
}


