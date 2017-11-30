/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Light.h"


//-------------------------------------------------------//
Light::Light(const char *szName, PinballMaster *pinball, int port):Output(szName, pinball, port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Light Constructor");
	#endif

	m_timerBlinking = new Timer(700, "TBlink", this->m_pinball,this,TimerType::continuous);
}

//-------------------------------------------------------//
Light::~Light()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Light Destructor");
	#endif

	delete m_timerBlinking;
}

//-------------------------------------------------------//
bool Light::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Light::NotifyEvent");
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
void Light::StartBlink(long value)
//-----------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output::StartBlink");
	#endif

	m_timerBlinking->ChangeValue(value);
}

//-----------------------------------------------------//
void Light::EndBlink()
//-----------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Output::EndBlink");
	#endif

	m_timerBlinking->Disable();
}


