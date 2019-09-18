/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Light.h"

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

	//delete m_timerBlinking;
}

//-------------------------------------------------------//
bool Light::NotifyEvent(Object * /*sender*/, uint8_t event, uint8_t /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Light::NotifyEvent"));
	#endif

	if (event == EVENT_TIMEISOVER)
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
void Light::StartBlink(unsigned long value)
//-----------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Output::StartBlink"));
	#endif

	m_timerBlinking->ChangeTimerValue(value);
	m_timerBlinking->Start();
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


