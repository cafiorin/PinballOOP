/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ReturnKickBall.h"
#include "PinballMaster.h"
#include "PinballObject.h"
#include "Input.h"
#include "Output.h"
#include "Timer.h"

//-------------------------------------------------------//
ReturnKickBall::ReturnKickBall(const char *szName, PinballMaster *pinball, int portNumberInput, int portNumberOutput,int led) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("ReturnKickBall Constructor");
	#endif

	m_led = led;

	m_input1 = new Input("ReIn", pinball, portNumberInput,this);
	m_output = new Output("ReOut", pinball, portNumberOutput);

	m_returnBallOn = true;
	m_timerBlinkLed = new Timer(400, "TTLB", pinball, this, TimerType::continuous);
	m_timerBlinkLed->Disable();
}

//-------------------------------------------------------//
bool ReturnKickBall::Init(StatusPinball status)
//-------------------------------------------------------//
{
	if (status == StatusPinball::playingmode)
	{
		m_returnBallOn = true;
		m_timerBlinkLed->Disable();
		LedControl *ledControl = m_pinball->GetLedControl();
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
	Debug("ReturnKickBall Destructor");
	#endif
	
	delete m_timerBlinkLed;
	delete m_input1;
	delete m_output;
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
		LedControl *ledControl = m_pinball->GetLedControl();
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_led);
		}
	}
}

//-------------------------------------------------------//
bool ReturnKickBall::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("ReturnKickBall::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		if (m_returnBallOn)
		{
			m_output->TurnOnByTimer(TIME_COIL_ON);
		}
		m_pinball->NotifyEvent(this, event, valueToSend);
		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		if (m_pinball->IsPlaying())
		{
			LedControl *ledControl = m_pinball->GetLedControl();
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
