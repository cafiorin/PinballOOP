/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Target.h"
#include "..\\BitInput.h"
#include "..\\NewTimer.h"
#include "..\\LedControl.h"
#include "..\\Subject.h"

//-------------------------------------------------------//
Target::Target(BitInput* input, LedControl* ledControl, byte led) : Observer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Target Constructor"));
	#endif
	m_EventToHitTarget = NULL;

	input->AddObserverToEdgePositive(this);
	m_hit = false;
	m_led = led;
	m_LedControl = ledControl;
	m_timerBlinkLed = new NewTimer(400, NewTimerType::continuous,this);
}

//-------------------------------------------------------//
Target::~Target()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Target Destructor"));
	#endif
	
	delete m_timerBlinkLed;
	delete m_EventToHitTarget;
}

//-------------------------------------------------------//
void Target::StartPlayMode()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Target::StartPlayMode"));
	#endif

	m_timerBlinkLed->Start();
	m_hit = false;
}

//-------------------------------------------------------//
void Target::onNotifySubject(EventType event, byte value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Target::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		m_timerBlinkLed->Stop();
		m_LedControl->TurnOn(m_led);
		m_hit = true;

		if (m_EventToHitTarget != NULL)
		{
			m_EventToHitTarget->notifyObserver();
		}
	}
	else if (event == EventType::TimeIsOver)
	{
		//TODO if (m_Pinball->IsPlaying())
		//{
		if (m_LedControl->IsTurn(m_led))
			m_LedControl->TurnOff(m_led);
		else
			m_LedControl->TurnOn(m_led);
		//}
	}
}

//------------------------------------------------//
void Target::AddObserverToSlingShotActivated(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToHitTarget == NULL)
	{
		m_EventToHitTarget = new Subject(EventType::SlingShotActivated);
	}

	m_EventToHitTarget->registerObserver(observer);
}

