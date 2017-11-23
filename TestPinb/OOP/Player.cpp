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
	m_Stage = NULL;
	m_Status = StatusPlayer::waiting;
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
	#ifdef DEBUGMESSAGES
	LogMessage("Player::Init");
	#endif

	m_Status = StatusPlayer::waiting;
	this->m_Stage = m_PinballMaster->GetStage(0);
	this->m_nBalls = m_PinballMaster->GetBallsByPlayer();
	m_Score = 0;
	m_ExtraBall = false;
	m_Multiply = 1;

	return true;
}

//-------------------------------------------------------//
void Player::SetNextStage()
//-------------------------------------------------------//
{
	this->m_Stage = m_PinballMaster->GetStage(0);
	this->m_Stage->SetCurrentPlayer(this);
}

//-------------------------------------------------------//
bool Player::Loop(int value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("Player::Loop");
	#endif

	if (m_Status == StatusPlayer::playing)
	{
		if (m_Stage != NULL)
		{
			m_Stage->Loop(value);
		}
	}
	return false;
}

//-------------------------------------------------------//
bool Player::SetCurrentPlayer(int indexPlayer)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::SetCurrentPlayer");
	#endif

	if (m_Status == StatusPlayer::waiting)
	{
		Player::m_indexPlayerCurrent = indexPlayer;
		m_Status = StatusPlayer::playing;
		
		if (m_Stage != NULL)
		{
			m_Stage->SetCurrentPlayer(this);
		}

		m_PinballMaster->GetNewBall();

		DisplayScore();
		return true;
	}

	return false;
}

//-------------------------------------------------------//
void Player::LostBall()
//-------------------------------------------------------//
{
	m_Status = StatusPlayer::waiting;
	m_nBalls--;
	if (m_nBalls <= 0)
	{
		//Game Over to this player
		m_Status = StatusPlayer::gameover;
	}
}

//-------------------------------------------------------//
void Player::DisplayScore()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::DisplayScore");
	#endif

	char szPlayer[10];
	sprintf(szPlayer, "Jog %d", Player::m_indexPlayerCurrent+1);

	char szPlayerScore[10];
	sprintf(szPlayerScore, "%05d", m_Score);

	m_PinballMaster->printText(szPlayer, szPlayerScore, 1);
}

//---------------------------------------------------------------------//
bool Player::SetNextMultiply()
//---------------------------------------------------------------------//
{
	if (m_Multiply < MAX_MULTIPLY)
	{
		m_Multiply++;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------//
bool Player::SetExtraBall()
//---------------------------------------------------------------------//
{
	if (!m_ExtraBall)
	{
		m_ExtraBall = true;
		return true;
	}
	return false;
}


//---------------------------------------------------------------------//
bool Player::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Player::NotifyEvent");
	#endif

	if (m_Status == StatusPlayer::playing)
	{
		if (m_Stage != NULL)
		{
			if (event == EVENT_DROPTARGETDOWN || (valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH))
			{
				int score = m_Stage->PlayfieldEvent(sender, event, valueToSend);
				m_Score += (score * m_Multiply);
				DisplayScore();
				return true;
			}
		}
	}

	return false;
}
