/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "KickoutHole.h"
#include "BitInput.h"
#include "BitOutput.h"
#include "NewTimer.h"
#include "Observer.h"
#include "Subject.h"
#include "Initializable.h"
#include "Logger.h"

//-------------------------------------------------------//
KickoutHole::KickoutHole(BitInput* input, BitOutput* output) : Observer(), Initializable()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("KickoutHole Constructor"));
	#endif
	
	m_EventToBallKickHole = NULL;
	
	m_input = input;
	input->AddObserverToEdgePositive(this);
	
	m_TimerAvoidOn = new NewTimer(300, NewTimerType::once, this);
	//m_TimerAvoidOn->AddObserverToTimeIsOver(this);

	m_output = output;
}

//-------------------------------------------------------//
KickoutHole::~KickoutHole()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("KickoutHole Destructor"));
	#endif

	delete m_EventToBallKickHole;
	delete m_TimerAvoidOn;
}

//-------------------------------------------------------//
void KickoutHole::init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("KickoutHole::Init"));
	#endif

	LanchBall();
}

//-------------------------------------------------------//
void KickoutHole::onNotifySubject(EventType event, byte /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("KickoutHole::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		if (m_EventToBallKickHole != NULL)
		{
			m_EventToBallKickHole->notifyObserver();
		}
		else
		{
			LanchBall();
		}

	}
}


//-------------------------------------------------------//
void KickoutHole::LanchBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("KickoutHole::LanchBall"));
	#endif

	if (m_input->GetInput() && !m_TimerAvoidOn->IsRunning())
	{
		m_output->TurnOnByTimer();
		m_TimerAvoidOn->Start();
	}
}

//------------------------------------------------//
void KickoutHole::AddObserverToBallKickHole(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToBallKickHole == NULL)
	{
		m_EventToBallKickHole = new Subject(EventType::BallKickHole, m_input->GetPortNumber());
	}

	m_EventToBallKickHole->registerObserver(observer);
}
