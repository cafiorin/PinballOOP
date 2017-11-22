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
KickoutHole::KickoutHole(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput,Multiplex *multiplex) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("KickoutHole Constructor");
	#endif

	m_input1 = new Input("KHIn", pinball, portNumberInput,this);
	m_output = new Output("KHOut", pinball, portNumberOutput,multiplex);

	Init();
}

//-------------------------------------------------------//
KickoutHole::~KickoutHole()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("KickoutHole Destructor");
	#endif
	
	delete m_input1;
	delete m_output;
}

//-------------------------------------------------------//
bool KickoutHole::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("KickoutHole::Init");
	#endif

	m_ball = false;
	if (m_input1->GetInput())
	{
		m_output->TurnOnByTimer();
	}

	return true;
}

//-------------------------------------------------------//
bool KickoutHole::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("KickoutHole::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_ball = true;
		m_pinball->NotifyEvent(this, event, valueToSend);
		return true;
	}
	return false;
}


//-------------------------------------------------------//
void KickoutHole::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("KickoutHole::LanchBall");
	#endif

	if (m_ball)
	{
		m_ball = false;
		m_output->TurnOnByTimer(TIME_COIL_ON);
	}
}