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
	#ifdef DEBUGMESSAGESCREATION
	Debug("AttractMode Construct");
	#endif

	m_timerGameOver = new Timer(1000, "TimerGO", pinball, this, TimerType::continuous);
	m_showGameOver = false;
}

//-----------------------------------------------------------
AttractMode::~AttractMode()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("AttractMode Destruct");
	#endif

	delete m_timerGameOver;
}


//-----------------------------------------------------------
bool AttractMode::Init()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("AttractMode::Init");
	#endif

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
	#ifdef DEBUGMESSAGES
	Debug("AttractMode::InitGameOver");
	#endif

	m_PinballMaster->printText("GAME", "OVER", 0);
	m_timerGameOver->Enable();
	m_showGameOver = true;
	m_showAlternate = true;
}

//---------------------------------------------------------------------//
bool AttractMode::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("AttractMode::NotifyEvent");
	#endif

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
		Debug("AttractMode::TimerIsOver");
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
