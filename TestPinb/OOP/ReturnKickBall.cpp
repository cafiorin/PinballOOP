/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ReturnKickBall.h"
#include "Pinball.h"
#include "PinballObject.h"

//-------------------------------------------------------//
ReturnKickBall::ReturnKickBall(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput,Multiplex *multiplex) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("ReturnKickBall Constructor");
	#endif

	m_input1 = new Input("ReIn", pinball, portNumberInput,this);
	m_output = new Output("ReOut", pinball, portNumberOutput,multiplex);

	Init();
}

//-------------------------------------------------------//
ReturnKickBall::~ReturnKickBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("ReturnKickBall Destructor");
	#endif
	
	delete m_input1;
	delete m_output;
}

//-------------------------------------------------------//
bool ReturnKickBall::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("ReturnKickBall::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_output->TurnOnByTimer(TIME_COIL_ON);
		return true;
	}
	return false;
}
