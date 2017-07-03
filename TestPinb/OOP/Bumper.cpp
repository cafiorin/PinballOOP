/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Bumper.h"
#include "PinballObject.h"

//-------------------------------------------------------//
Bumper::Bumper(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Bumper Constructor");
	#endif

	m_input = new Input("BperIn", pinball, portNumberInput);
	m_output = new Output("BperOut", pinball, portNumberOutput);

	Init();
}

//-------------------------------------------------------//
Bumper::~Bumper()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Bumper Destructor");
	#endif

	delete m_input;
	delete m_output;
}

//-------------------------------------------------------//
bool Bumper::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Bumper Init");
	#endif

	return false;
}

//-------------------------------------------------------//
bool Bumper::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("Bumper Loop");
		#endif

		if (m_input->CheckEdgePositive())
		{
			m_output->TurnOnByTimer(TIME_COIL_ON);
		}
	}

	return false;
}