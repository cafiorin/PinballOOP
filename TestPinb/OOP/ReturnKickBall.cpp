/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ReturnKickBall.h"
#include "Pinball.h"
#include "PinballObject.h"
#include "Input.h"
#include "Output.h"
#include "Timer.h"
#include "LedControl.h"

//-------------------------------------------------------//
ReturnKickBall::ReturnKickBall(uint8_t portNumberInput, uint8_t portNumberOutput,uint8_t led) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("ReturnKickBall Constructor"));
	#endif

	m_led = led;

	m_input1 = new Input(portNumberInput,this);
	m_output = new Output(portNumberOutput);

	m_returnBallOn = true;
	m_timerBlinkLed = new Timer(400, this, TimerType::continuous);
	m_timerBlinkLed->Disable();
}

//-------------------------------------------------------//
bool ReturnKickBall::Init()
//-------------------------------------------------------//
{
	if (m_Pinball->GetStatus() == StatusPinball::playingmode)
	{
		m_returnBallOn = true;
		m_timerBlinkLed->Disable();
		LedControl *ledControl = m_Pinball->GetLedControl();
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_led);
		}
	}
	return true;
}

//-------------------------------------------------------//
ReturnKickBall::~ReturnKickBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("ReturnKickBall Destructor"));
	#endif
	/*
	delete m_timerBlinkLed;
	delete m_input1;
	delete m_output;
	*/
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
		m_timerBlinkLed->Disable();
		LedControl *ledControl = m_Pinball->GetLedControl();
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_led);
		}
	}
}

//-------------------------------------------------------//
bool ReturnKickBall::NotifyEvent(Object *sender, uint8_t event, uint8_t value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("ReturnKickBall::NotifyEvent"));
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		if (m_returnBallOn)
		{
			m_output->Pulse();
		}
		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		if (m_Pinball->IsPlaying())
		{
			LedControl *ledControl = m_Pinball->GetLedControl();
			if (ledControl != NULL)
			{
				if (ledControl->IsTurn(m_led))
					ledControl->TurnOff(m_led);
				else
					ledControl->TurnOn(m_led);
			}
		}

		return true;
	}
	return false;
}
