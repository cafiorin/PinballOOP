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
#include "..\\Logger.h"
#include "..\\ChangeableStatus.h"

//-------------------------------------------------------//
ReturnKickBall::ReturnKickBall(BitInput* input, BitOutput *output, LedControl *ledControl, byte led) : Observer(), ChangeableStatus()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("ReturnKickBall Constructor"));
	#endif

	m_status = StatusPinballMachine::initializing;
	m_led = led;
	m_LedControl = ledControl;

	m_input1 = input;
	m_output = output;

	m_timerBlinkLed = new NewTimer(400, NewTimerType::continuous, this);
	SetReturnBall(false);
}

//-------------------------------------------------------//
ReturnKickBall::~ReturnKickBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("ReturnKickBall Destructor"));
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
		m_LedControl->TurnOff(m_led);
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
	Logger::LogMessage(F("ReturnKickBall::NotifyEvent"));
	#endif
	if (m_status == StatusPinballMachine::playingmode)
	{
		if (event == EventType::EdgePositive)
		{
			if (m_returnBallOn)
			{
				m_output->Pulse();
			}
		}
		else if (event == EventType::TimeIsOver)
		{
			if (m_LedControl->IsTurn(m_led))
				m_LedControl->TurnOff(m_led);
			else
				m_LedControl->TurnOn(m_led);
		}
	}
}

//-------------------------------------------------------//
void ReturnKickBall::changeStatus(StatusPinballMachine status)
//-------------------------------------------------------//
{
	m_status = status;
	if (m_status == StatusPinballMachine::initplaymode)
	{
		SetReturnBall(true);
	}
}
