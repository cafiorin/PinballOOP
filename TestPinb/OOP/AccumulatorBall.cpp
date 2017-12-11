/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AccumulatorBall.h"
#include "PinballMaster.h"
#include "PinballObject.h"

//-------------------------------------------------------//
AccumulatorBall::AccumulatorBall(const char *szName, PinballMaster *pinball, int portNumberInput1, int portNumberInput2, int portNumberInput3, int portNumberInput4, int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("AccumulatorBall Constructor");
	#endif

	m_input1 = new Input("AccIn1", pinball, portNumberInput1,this);
	m_input1->SetDebounceRead(5);
	
	m_input2 = new Input("AccIn2", pinball, portNumberInput2, this);
	m_input2->SetDebounceRead(5);
	
	m_input3 = new Input("AccIn3", pinball, portNumberInput3, this);
	m_input3->SetDebounceRead(5);
	
	m_input4 = new Input("AccIn4", pinball, portNumberInput4, this);
	m_input4->SetDebounceRead(5);

	m_output = new Output("ReOut", pinball, portNumberOutput);

	m_nBalls = 0;
}

//-------------------------------------------------------//
AccumulatorBall::~AccumulatorBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("AccumulatorBall Destructor");
	#endif
	
	delete m_input1;
	delete m_input2;
	delete m_input3;
	delete m_input4;

	delete m_output;
}

//-------------------------------------------------------//
bool AccumulatorBall::Init(StatusPinball status)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("AccumulatorBall::Init");
	#endif

	int nTries = 5;
	while (m_nBalls > 0 || nTries > 0)
	{
		if (m_input1->GetInput())
		{
			LanchBall();
			delay(1000);
		}
		nTries--;
	}

	m_nBalls = 0;

	return true;
}


//-------------------------------------------------------//
bool AccumulatorBall::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("AccumulatorBall::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		if(valueToSend == m_input1->GetPortNumber())
		{
			m_nBalls = 1;
		}
		else if (valueToSend == m_input2->GetPortNumber())
		{
			m_nBalls = 2;
		}
		else if (valueToSend == m_input3->GetPortNumber())
		{
			m_nBalls = 3;
		}
		else if (valueToSend == m_input4->GetPortNumber())
		{
			m_nBalls = 4;
		}

		return true;
	}
	return false;
}

//-------------------------------------------------------//
void AccumulatorBall::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("AccumulatorBall::LanchBall");
	#endif

	if (m_nBalls >= 1)
	{
		m_nBalls--;
		m_output->TurnOnByTimer(TIME_COIL_ON);
	}
}