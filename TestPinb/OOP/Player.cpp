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
	#ifdef DEBUGMESSAGESCREATION
	LogMessage("Player Constructor");
	#endif

	m_Stage = NULL;
	m_Status = StatusPlayer::waiting;
}

//-------------------------------------------------------//
Player::~Player()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage("Player Destructor");
	#endif
}


//-------------------------------------------------------//
bool Player::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::Init");
	#endif

	m_Status = StatusPlayer::waiting;
	this->m_Stage = m_pinball->GetStage(0);
	this->m_nBalls = m_pinball->GetBallsByPlayer();
	m_Score = 0;
	m_ExtraBall = false;
	m_Multiply = 1;

	return true;
}

//-------------------------------------------------------//
void Player::SetNextStage()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::SetNextStage");
	#endif

	this->m_Stage = m_pinball->GetStage(0);
	this->m_Stage->SetCurrentPlayer(this);
}

//-------------------------------------------------------//
bool Player::SetCurrentPlayer(int indexPlayer)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::SetCurrentPlayer");
	#endif

	if (this->m_nBalls <= 0 || m_Status == StatusPlayer::gameover)
	{
		return false;
	}

	if (m_Status == StatusPlayer::waiting)
	{
		Player::m_indexPlayerCurrent = indexPlayer;
		m_Status = StatusPlayer::playing;
		
		if (m_Stage != NULL)
		{
			m_Stage->SetCurrentPlayer(this);
		}

		m_pinball->GetNewBall();

		DisplayScore();
		return true;
	}

	return false;
}

//-------------------------------------------------------//
void Player::LostBall()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::LostBall");
	#endif

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

	m_pinball->printText(szPlayer, szPlayerScore, 1);
}

//---------------------------------------------------------------------//
bool Player::SetNextMultiply()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Player::SetNextMultiply");
	#endif

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
	#ifdef DEBUGMESSAGES
	LogMessage("Player::SetExtraBall");
	#endif

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
