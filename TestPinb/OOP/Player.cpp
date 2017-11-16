/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Player.h"
#include "PinballObject.h"
#include "PinballMaster.h"

int Player::m_indexPlayerCurrent = 0;

//-------------------------------------------------------//
Player::Player(PinballMaster *pinball):PinballObject("Player",pinball)
//-------------------------------------------------------//
{
	m_PinballMaster = pinball;
}

//-------------------------------------------------------//
Player::~Player()
//-------------------------------------------------------//
{
}


//-------------------------------------------------------//
bool Player::Init()
//-------------------------------------------------------//
{
	this->m_Stage = m_PinballMaster->GetStage(0);
	this->m_nBalls = MAX_BALLS;
	m_Score = 0;
	m_ExtraBall = false;
	m_Status = StatusPlayer::waiting;
	
	return true;
}

//-------------------------------------------------------//
bool Player::Loop(int value)
//-------------------------------------------------------//
{
	if (m_Status == StatusPlayer::playing)
	{
		m_Stage->Loop(value);
	}
	return false;
}

//-------------------------------------------------------//
void Player::SetCurrentPlayer(int indexPlayer)
//-------------------------------------------------------//
{
	Player::m_indexPlayerCurrent = indexPlayer;
	m_Status = StatusPlayer::playing;

	DisplayScore();
}

//-------------------------------------------------------//
void Player::DisplayScore()
//-------------------------------------------------------//
{
	char szPlayer[10];
	sprintf(szPlayer, "Jog %d", Player::m_indexPlayerCurrent+1);

	char szPlayerScore[10];
	sprintf(szPlayerScore, "%05d", m_Score);

	m_PinballMaster->printText(szPlayer, szPlayerScore, 0);
}

//---------------------------------------------------------------------//
bool Player::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::NotifyEvent Test");
	#endif

	if (event == EVENT_DROPTARGETDOWN)
	{
		//TODO:
		m_Score += 100;
		DisplayScore();
	}
	else
	{
		// -- P L A Y F I E L D --
		if (valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
		{
			m_Score += 1;
			DisplayScore();
		}
	}

	return false;
}
