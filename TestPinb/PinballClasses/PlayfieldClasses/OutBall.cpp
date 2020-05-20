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
#include "..\\BitInput.h"
#include "..\\BitOutput.h"
#include "..\\Observer.h"
#include "..\\Subject.h"
#include "..\\Utils.h"
#include "..\\Initializable.h"
#include "..\\Logger.h"

//-------------------------------------------------------//
OutBall::OutBall(BitInput* input1, BitOutput* output1, BitInput* input2, BitOutput* output2) : Observer(), Initializable()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("OutBall Constructor"));
	#endif
	m_EventToLostBall = NULL;

	m_input1 = input1;
	m_input1->AddObserverToEdgePositive(this);
	m_output1 = output1;
	m_input2 = input2;
	m_output2 = output2;

	m_nBalls = 4;
}

//-------------------------------------------------------//
OutBall::~OutBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("OutBall Destructor"));
	#endif

	delete m_EventToLostBall;
}

//-------------------------------------------------------//
void OutBall::init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("OutBall::Init"));
	#endif

	if (m_input1->GetInput() && m_input2->GetInput())
	{
		m_nBalls = 4;
	}
	else
	{
		byte nTries = 0;
		while (m_input1->GetInput() && !m_input2->GetInput() && nTries < 5)
		{
			m_output1->Pulse(40);
			delay(500);
			nTries++;
		}

		if (nTries < 5)
		{
			m_nBalls = 4;
		}
	}

	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("OutBall::Init Error"));
	#endif
}

//-------------------------------------------------------//
void OutBall::onNotifySubject(EventType event, byte value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("OutBall::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive && 
		value == m_input1->GetPortNumber())
	{
		AddBall();

		if (m_EventToLostBall != NULL)
		{
			m_EventToLostBall->notifyObserver();
		}

		if (m_input1->GetInput() && !m_input2->GetInput())
		{
			m_output1->Pulse(40);
		}
	}
}

//-------------------------------------------------------//
void OutBall::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("OutBall::LanchBall"));
	#endif

	if (m_nBalls > 0)
	{
		RemoveBall();
		m_output2->Pulse(800);
		delay(300);
		if (m_input1->GetInput() && !m_input2->GetInput())
		{
			m_output1->Pulse(40);
		}
	}

}

//------------------------------------------------//
void OutBall::AddObserverToLostBall(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToLostBall == NULL)
	{
		m_EventToLostBall = new Subject(EventType::LostBall);
	}

	m_EventToLostBall->registerObserver(observer);
}
