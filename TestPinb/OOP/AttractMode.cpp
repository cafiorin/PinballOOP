/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AttractMode.h"
#include "StageBase.h"
#include "Timer.h"
#include "PinballMaster.h"
#include "DefinesMp3.h"

//-----------------------------------------------------------
AttractMode::AttractMode(PinballMaster *pinball):StageBase(pinball,-1)
//-----------------------------------------------------------
{
	m_timerGameOver = new Timer(1000, "TimerGO", pinball, this, TimerType::continuous);
	m_showGameOver = false;
}

//-----------------------------------------------------------
AttractMode::~AttractMode()
//-----------------------------------------------------------
{
	delete m_timerGameOver;
}


//-----------------------------------------------------------
bool AttractMode::Init()
//-----------------------------------------------------------
{
	m_PinballMaster->sendMessageToAnotherArduino(ADDRESS_SLAVE, INIT_THEME);
	m_PinballMaster->printText("PRESS", "START", 0);
	m_showGameOver = false;
    m_PinballMaster->playSong(MP3_THEME00);
	return true;
}

//-----------------------------------------------------------
void AttractMode::InitGameOver()
//-----------------------------------------------------------
{
	m_PinballMaster->printText("GAME", "OVER", 0);
	m_timerGameOver->Enable();
	m_showGameOver = true;
	m_showAlternate = true;
}

//-----------------------------------------------------------
void AttractMode::Loop()
//-----------------------------------------------------------
{
	m_PinballMaster->m_LedControl->Loop();
}

//---------------------------------------------------------------------//
bool AttractMode::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	// -- T I M E R  I S  O V E R --
	if (event == EVENT_TIMEISOVER)
	{
		return TimerIsOver(sender);
	}

	return false;
}


//---------------------------------------------------------------------//
bool AttractMode::TimerIsOver(PinballObject *sender)
//---------------------------------------------------------------------//
{
	if (sender == m_timerGameOver && m_showGameOver)
	{
		#ifdef DEBUGMESSAGES
		Debug("...Timer is over game over");
		#endif
		if (m_showAlternate)
		{
			m_PinballMaster->printText("PRESS", "START", 0);
		}
		else
		{
			m_PinballMaster->printText("GAME", "OVER", 0);
		}

		m_showAlternate = !m_showAlternate;
		m_timerGameOver->Enable();
		return true;
	}

	return false;
}
