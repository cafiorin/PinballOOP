/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ReturnKickBall.h"
#include "..\\BitInput.h"
#include "..\\BitOutput.h"
#include "..\\Observer.h"
#include "..\\Subject.h"
#include "..\\NewTimer.h"
#include "..\\Utils.h"
#include "..\\LedControl.h"

//-------------------------------------------------------//
ReturnKickBall::ReturnKickBall(BitInput* input, BitOutput *output, LedControl *ledControl, byte led) : Observer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("ReturnKickBall Constructor"));
	#endif

	m_led = led;
	m_LedControl = ledControl;

	m_input1 = input;
	m_output = output;

	m_returnBallOn = true;
	m_timerBlinkLed = new NewTimer(400, NewTimerType::continuous, this);
}

//-------------------------------------------------------//
void ReturnKickBall::StartPlayMode()
//-------------------------------------------------------//
{
	m_returnBallOn = true;
	m_timerBlinkLed->Stop();
	m_LedControl->TurnOn(m_led);
}

//-------------------------------------------------------//
ReturnKickBall::~ReturnKickBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("ReturnKickBall Destructor"));
	#endif
	delete m_timerBlinkLed;
}

//-------------------------------------------------------//
void ReturnKickBall::SetReturnBall(bool returnBallOn)
//-------------------------------------------------------//
{
	m_returnBallOn = returnBallOn;
	if (!m_returnBallOn)
	{
		m_timerBlinkLed->Start();
	}
	else
	{
		m_timerBlinkLed->Stop();
		m_LedControl->TurnOn(m_led);
	}
}

//-------------------------------------------------------//
void ReturnKickBall::onNotifySubject(EventType event, byte /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("ReturnKickBall::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		if (m_returnBallOn)
		{
			m_output->Pulse();
		}
	}
	else if (event == EventType::TimeIsOver)
	{
		//TODO: if (m_Pinball->IsPlaying())
		if (m_LedControl->IsTurn(m_led))
			m_LedControl->TurnOff(m_led);
		else
			m_LedControl->TurnOn(m_led);
	}
}
