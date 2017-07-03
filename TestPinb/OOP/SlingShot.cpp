/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SlingShot.h"
#include "PinballObject.h"

//-------------------------------------------------------//
SlingShot::SlingShot(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberInput2, int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SlingShot Constructor");
	#endif

	m_input1 = new Input("SLIn1", pinball, portNumberInput1);
	m_input2 = new Input("SLIn2", pinball, portNumberInput2);
	
	m_output = new Output("SLOut", pinball, portNumberOutput);

	Init();
}

//-------------------------------------------------------//
SlingShot::~SlingShot()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SlingShot Destructor");
	#endif

	delete m_input1;
	delete m_input2;
	delete m_output;
}

//-------------------------------------------------------//
bool SlingShot::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SlingShot Init");
	#endif

	return false;
}

//-------------------------------------------------------//
bool SlingShot::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("SlingShot Loop");
		#endif

		if (m_input1->CheckEdgePositive() || m_input2->CheckEdgePositive())
		{
			m_output->TurnOnByTimer(TIME_COIL_ON);
		}
	}

	return false;
}