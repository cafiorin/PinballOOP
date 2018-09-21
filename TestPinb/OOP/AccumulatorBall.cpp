/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AccumulatorBall.h"
#include "Event.h"
#include "PinballObject.h"
#include "Pinball.h"

//-------------------------------------------------------//
AccumulatorBall::AccumulatorBall(uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberInput3, uint8_t portNumberInput4, uint8_t portNumberOutput) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("AccumulatorBall Constructor"));
	#endif

	m_input1 = new Input(portNumberInput1,this);
	m_input1->SetDebounceRead(5);
	
	m_input2 = new Input(portNumberInput2, this);
	m_input2->SetDebounceRead(5);
	
	m_input3 = new Input(portNumberInput3, this);
	m_input3->SetDebounceRead(5);
	
	m_input4 = new Input(portNumberInput4, this);
	m_input4->SetDebounceRead(5);

	m_output = new Output(portNumberOutput);

	m_nBalls = 0;
}

//-------------------------------------------------------//
AccumulatorBall::~AccumulatorBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("AccumulatorBall Destructor"));
	#endif
	
	/*
	delete m_input1;
	delete m_input2;
	delete m_input3;
	delete m_input4;

	delete m_output;
	*/
}

//-------------------------------------------------------//
bool AccumulatorBall::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("AccumulatorBall::Init"));
	#endif

	if (m_Pinball->GetStatus() == StatusPinball::initializing)
	{
		uint8_t nTries = 5;
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
	}

	return true;
}


//-------------------------------------------------------//
bool AccumulatorBall::NotifyEvent(Object *sender, Event *event)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("AccumulatorBall::NotifyEvent"));
	#endif

	if (event->GetIdEvent() == EVENT_EDGEPOSITIVE)
	{
		bool input1 = m_input1->GetInput();
		bool input2 = m_input2->GetInput();
		bool input3 = m_input3->GetInput();
		bool input4 = m_input4->GetInput();

		m_nBalls = (int)input1 + (int)input2 + (int)input3 + (int)input4;
		return true;
	}
	return false;
}

//-------------------------------------------------------//
void AccumulatorBall::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("AccumulatorBall::LanchBall"));
	#endif

	if (m_nBalls >= 1)
	{
		m_nBalls--;
		m_output->TurnOnByTimer(TIME_COIL_ON);
	}
}