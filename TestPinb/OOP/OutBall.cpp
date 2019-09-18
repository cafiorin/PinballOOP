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
OutBall::OutBall(uint8_t portNumberInput1, uint8_t portNumberOutput1, uint8_t portNumberInput2, uint8_t portNumberOutput2) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("OutBall Constructor"));
	#endif

	m_input1 = new Input(portNumberInput1,this);
	m_output1 = new Output(portNumberOutput1);
	m_input2 = new Input(portNumberInput2,this);
	m_output2 = new Output(portNumberOutput2);

	m_nBalls = 4;
}

//-------------------------------------------------------//
OutBall::~OutBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("OutBall Destructor"));
	#endif
	/*
	delete m_input1;
	delete m_input2;
	delete m_output1;
	delete m_output2;
	*/
}

//-------------------------------------------------------//
bool OutBall::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("OutBall::Init"));
	#endif

	if (m_input1->GetInput() && m_input2->GetInput())
	{
		m_nBalls = 4;
		return true;
	}
	else
	{
		uint8_t nTries = 0;
		while (m_input1->GetInput() && !m_input2->GetInput() && nTries < 5)
		{
			m_output1->TurnOnByDelay();
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
	LogMessage(F("OutBall::Init Error"));
	#endif

	return false;
}

//-------------------------------------------------------//
bool OutBall::NotifyEvent(Object * /*sender*/, uint8_t event, uint8_t /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("OutBall::NotifyEvent"));
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		AddBall();

		m_Pinball->NotifyEvent(this, EVENT_LOST_BALL,0);
		if (m_input1->GetInput() && !m_input2->GetInput())
		{
			m_output1->TurnOnByTimer();
		}
		return true;
	}
	return false;
}

//-------------------------------------------------------//
void OutBall::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("OutBall::LanchBall"));
	#endif

	if (m_nBalls > 0)
	{
		RemoveBall();
		m_output2->TurnOnByTimer();

		if (m_input1->GetInput() && !m_input2->GetInput())
		{
			m_output1->TurnOnByTimer();
		}
	}

}