/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Light.h"


//-------------------------------------------------------//
Light::Light(const char *szName, Pinball *pinball, int port, Multiplex *multiplex):Output(szName, pinball, port,multiplex)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("Light Constructor");
#endif

	m_timerBlinking = new Timer(700, "TBlink", this->m_pinball);

	Init();
}

//-------------------------------------------------------//
Light::~Light()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("Light Destructor");
#endif
}

//-------------------------------------------------------//
bool Light::Init()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("Light::Init");
#endif

	return Output::Init();
}

//-------------------------------------------------------//
bool Light::Loop(int value)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGESLOOP
	Debug("Output::Loop");
#endif

	if (m_timerBlinking->Check())
	{
		if (this->IsTurnOn())
			TurnOff();
		else
			TurnOn();

		m_timerBlinking->Start();
	}

	return Output::Loop(value);
}

void Light::StartBlink(long value)
{
	m_timerBlinking->ChangeValue(value);
}

void Light::EndBlink()
{
	m_timerBlinking->Disable();
}


