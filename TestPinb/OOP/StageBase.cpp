#include "StageBase.h"
#include "PinballMaster.h"
#include "Player.h"

//---------------------------------------------------
StageBase::StageBase(PinballMaster *pinball, int number) : PinballObject("STAGE",pinball)
//---------------------------------------------------
{
	m_PinballMaster = pinball;
	m_number = number;
	m_currentPlayer = NULL;
}

//---------------------------------------------------
StageBase::~StageBase()
//---------------------------------------------------
{
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

	m_PinballMaster->m_LedControl->TurnOff(LED_ROLLOVER_CENTER);
	m_PinballMaster->m_LedControl->TurnOff(LED_ROLLOVER_LEFT);
	m_PinballMaster->m_LedControl->TurnOff(LED_ROLLOVER_RIGHT);

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
		bool allTargets = false;
		switch (valueToSend)
		{
		case INPUT_SW_ROLLOVER_CENTER:
			m_PinballMaster->m_LedControl->TurnOn(LED_ROLLOVER_CENTER);
			allTargets = CheckRolloversMultiply();
			break;

		case INPUT_SW_ROLLOVER_LEFT:
			m_PinballMaster->m_LedControl->TurnOn(LED_ROLLOVER_LEFT);
			allTargets = CheckRolloversMultiply();
			break;

		case INPUT_SW_ROLLOVER_RIGHT:
			m_PinballMaster->m_LedControl->TurnOn(LED_ROLLOVER_RIGHT);
			allTargets = CheckRolloversMultiply();
			break;
		}

		if(allTargets)
			return SCORE_ALL_TARGETS;
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

	m_PinballMaster->m_LedControl->TurnOff(LED_ROLLOVER_CENTER);
	m_PinballMaster->m_LedControl->TurnOff(LED_ROLLOVER_LEFT);
	m_PinballMaster->m_LedControl->TurnOff(LED_ROLLOVER_RIGHT);
}


//-----------------------------------------------------------
bool StageBase::CheckRolloversMultiply()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("StageBase::CheckRolloversMultiply");
	#endif

	if (m_PinballMaster->m_LedControl->IsTurn(LED_ROLLOVER_CENTER) &&
		m_PinballMaster->m_LedControl->IsTurn(LED_ROLLOVER_LEFT) &&
		m_PinballMaster->m_LedControl->IsTurn(LED_ROLLOVER_RIGHT))
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

	m_PinballMaster->m_LedControl->TurnOff(LED_MULTIPLY_2X);
	m_PinballMaster->m_LedControl->TurnOff(LED_MULTIPLY_3X);
	m_PinballMaster->m_LedControl->TurnOff(LED_MULTIPLY_4X);
	m_PinballMaster->m_LedControl->TurnOff(LED_MULTIPLY_5X);
	m_PinballMaster->m_LedControl->TurnOff(LED_MULTIPLY_6X);

	int multiply = m_currentPlayer->GetMultiply();
	if (multiply > 1)
	{
		m_PinballMaster->m_LedControl->TurnOn(LED_MULTIPLY_2X + multiply - 1);
	}
}
