/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//OutBall - To a Multiball game

// When Turn on the machine:
// input1 is on and input2 is on = OK


#include "OutBall.h"
#include "Pinball.h"

//-------------------------------------------------------//
OutBall::OutBall(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberOutput1, int portNumberInput2, int portNumberOutput2, Multiplex *multiplex) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("OutBall Constructor");
	#endif

	m_input1 = new Input("OBIn1", pinball, portNumberInput1,this);
	m_output1 = new Output("OBOut1", pinball, portNumberOutput1, multiplex);
	m_input2 = new Input("OBIn2", pinball, portNumberInput2,this);
	m_output2 = new Output("OBOut2", pinball, portNumberOutput2, multiplex);

	m_nBalls = 4;
	Init();
}

//-------------------------------------------------------//
OutBall::~OutBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("OutBall Destructor");
	#endif
	
	delete m_input1;
	delete m_input2;
	delete m_output1;
	delete m_output2;
}

//-------------------------------------------------------//
bool OutBall::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("OutBall::Init");
	#endif

	if (m_input1->GetInput() && m_input2->GetInput())
	{
		m_nBalls = 4;
		return true;
	}
	else
	{
		int nTries = 0;
		while (m_input1->GetInput() && !m_input2->GetInput() && nTries < 5)
		{
			m_output1->TurnOnByTimer();
			delay(1000);
			nTries++;
		}

		if (nTries < 5)
		{
			m_nBalls = 4;
			return true;
		}
	}

	#ifdef DEBUGMESSAGES
	Debug("OutBall::Init Error");
	#endif

	return false;
}

//-------------------------------------------------------//
bool OutBall::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("OutBall::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		AddBall();

		m_pinball->NotifyEvent(this, EVENT_LOST_BALL, 0);
		if (m_input1->GetInput() && !m_input2->GetInput())
		{
			m_output1->TurnOnByTimer();
		}
		return true;
	}
	return false;
}


//-------------------------------------------------------//
bool OutBall::Loop(int value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("OutBall::Loop");
	#endif

	return false;
}

//-------------------------------------------------------//
void OutBall::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("OutBall::LanchBall");
	#endif

	if (m_nBalls > 0)
	{
		RemoveBall();
		m_output2->TurnOnByTimer();

		if (m_input1->GetInput() && !m_input2->GetInput())
		{
			delay(50);
			m_output1->TurnOnByTimer();
		}
	}

}