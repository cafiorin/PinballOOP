/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AccumulatorBall.h"
#include "..\\MultiplexInputs.h"
#include "..\\LatchOutputs.h"
#include "..\\Observer.h"
#include "..\\Subject.h"
#include "..\\BitOutput.h"
#include "..\\BitInput.h"
#include "..\\Initializable.h"
#include "..\\utils.h"
#include "..\\Logger.h"

//-------------------------------------------------------//
AccumulatorBall::AccumulatorBall(byte portNumberInput1, 
								 byte portNumberInput2, 
								 byte portNumberInput3, 
								 byte portNumberInput4,
								 byte portNumberOutput,
								 MultiplexInputs* inputs,
								 LatchOutputs *outputHighVoltage) : Observer() , Initializable()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("AccumulatorBall Constructor"));
	#endif

	inputs->AddInputObserverToEdgePositive(portNumberInput1, this);
	inputs->AddInputObserverToEdgePositive(portNumberInput2, this);
	inputs->AddInputObserverToEdgePositive(portNumberInput3, this);
	inputs->AddInputObserverToEdgePositive(portNumberInput4, this);

	m_input1 = inputs->GetInput(portNumberInput1);
	m_input2 = inputs->GetInput(portNumberInput1);
	m_input3 = inputs->GetInput(portNumberInput1);
	m_input4 = inputs->GetInput(portNumberInput1);

	m_output = outputHighVoltage->GetOuput(portNumberOutput);

	m_nBalls = 0;
}

//-------------------------------------------------------//
AccumulatorBall::~AccumulatorBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("AccumulatorBall Destructor"));
	#endif
}

//-------------------------------------------------------//
void AccumulatorBall::init()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("AccumulatorBall::Init"));
#endif

	byte nTries = 5;
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


//-------------------------------------------------------//
void AccumulatorBall::onNotifySubject(EventType event, byte /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("AccumulatorBall::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		bool input1 = m_input1->GetInput();
		bool input2 = m_input2->GetInput();
		bool input3 = m_input3->GetInput();
		bool input4 = m_input4->GetInput();

		m_nBalls = (int)input1 + (int)input2 + (int)input3 + (int)input4;
	}
}

//-------------------------------------------------------//
void AccumulatorBall::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("AccumulatorBall::LanchBall"));
	#endif

	if (m_nBalls >= 1)
	{
		m_nBalls--;
	}

	m_output->Pulse();
}