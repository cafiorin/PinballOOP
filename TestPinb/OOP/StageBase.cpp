/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "StageBase.h"
#include "PinballMaster.h"
#include "SequencerLeds.h"
#include "Player.h"
#include "DefinesMp3.h"

//---------------------------------------------------
StageBase::StageBase(PinballMaster *pinball, int number) : PinballObject("STAGE",pinball)
//---------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("StageBase Constructor");
	#endif

	m_PinballMaster = pinball;
	m_number = number;
	m_currentPlayer = NULL;

	// Loop Leds
	m_LedsLoop = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsLoop->AddLed(LED_LOOP_B1);
	m_LedsLoop->AddLed(LED_LOOP_B2);
	m_LedsLoop->AddLed(LED_LOOP_A1, true);
	m_LedsLoop->AddLed(LED_LOOP_A2);

}

//---------------------------------------------------
StageBase::~StageBase()
//---------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("StageBase Destructor");
	#endif

	delete m_LedsLoop;
}

//---------------------------------------------------
void StageBase::SetCurrentPlayer(Player *player)
//---------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::SetCurrentPlayer");
	#endif

	m_currentPlayer = player;
	RestartPlayer();
}

//-----------------------------------------------------------
void StageBase::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::RestartPlayer");
	#endif
	
	m_LedsLoop->Start();

	LedControl *pLedControl = m_PinballMaster->GetLedControl();
	if (pLedControl != NULL)
	{
		pLedControl->TurnOff(LED_ROLLOVER_CENTER);
		pLedControl->TurnOff(LED_ROLLOVER_LEFT);
		pLedControl->TurnOff(LED_ROLLOVER_RIGHT);
	}

	SetMultiply();
}

//-----------------------------------------------------------
int StageBase::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::PlayfieldEvent");
	#endif

	if (event == EVENT_DROPTARGETDOWN)
	{
		return SCORE_DROPTARGETDOWN;
	}
	else if (valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		bool allRollovers = false;
		LedControl *pLedControl = m_PinballMaster->GetLedControl();
		switch (valueToSend)
		{
		case INPUT_SW_ROLLOVER_CENTER:
			pLedControl->TurnOn(LED_ROLLOVER_CENTER);
			allRollovers = CheckRolloversMultiply();
			break;

		case INPUT_SW_ROLLOVER_LEFT:
			pLedControl->TurnOn(LED_ROLLOVER_LEFT);
			allRollovers = CheckRolloversMultiply();
			break;

		case INPUT_SW_ROLLOVER_RIGHT:
			pLedControl->TurnOn(LED_ROLLOVER_RIGHT);
			allRollovers = CheckRolloversMultiply();
			break;
		}

		if (allRollovers)
		{
			m_PinballMaster->playSong(MP3_ALL_ROLLOVERS);
			return SCORE_ALL_TARGETS;
		}
	}
	return 0;
}

//-----------------------------------------------------------
void StageBase::TurnOffRolloversMultiply()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::TurnOffRolloversMultiply");
	#endif

	LedControl *pLedControl = m_PinballMaster->GetLedControl();
	if (pLedControl != NULL)
	{
		pLedControl->TurnOff(LED_ROLLOVER_CENTER);
		pLedControl->TurnOff(LED_ROLLOVER_LEFT);
		pLedControl->TurnOff(LED_ROLLOVER_RIGHT);
	}
}


//-----------------------------------------------------------
bool StageBase::CheckRolloversMultiply()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::CheckRolloversMultiply");
	#endif

	LedControl *pLedControl = m_PinballMaster->GetLedControl();

	if (pLedControl->IsTurn(LED_ROLLOVER_CENTER) &&
		pLedControl->IsTurn(LED_ROLLOVER_LEFT) &&
		pLedControl->IsTurn(LED_ROLLOVER_RIGHT))
	{
		if (m_currentPlayer != NULL)
		{
			if (m_currentPlayer->SetNextMultiply())
			{
				SetMultiply();
				TurnOffRolloversMultiply();
			}
		}
		return true;
	}
	return false;
}

//-----------------------------------------------------------
void StageBase::SetMultiply()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::SetMultiply");
	#endif

	LedControl *pLedControl = m_PinballMaster->GetLedControl();

	pLedControl->TurnOff(LED_MULTIPLY_2X);
	pLedControl->TurnOff(LED_MULTIPLY_3X);
	pLedControl->TurnOff(LED_MULTIPLY_4X);
	pLedControl->TurnOff(LED_MULTIPLY_5X);
	pLedControl->TurnOff(LED_MULTIPLY_6X);

	int multiply = m_currentPlayer->GetMultiply();
	if (multiply > 1)
	{
		pLedControl->TurnOn(LED_MULTIPLY_2X + multiply - 1);
	}
}
