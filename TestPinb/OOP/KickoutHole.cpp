/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "KickoutHole.h"

//-------------------------------------------------------//
KickoutHole::KickoutHole(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("KickoutHole Constructor");
	#endif

	m_input1 = new Input("KHIn", pinball, portNumberInput);
	m_output = new Output("KHOut", pinball, portNumberOutput);

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
		return true;
	}

	return false;
}

//-------------------------------------------------------//
bool KickoutHole::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("KickoutHole::Loop");
		#endif

		if (m_input1->CheckEdgePositive())
		{
			m_ball = true;
			return true;
		}
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