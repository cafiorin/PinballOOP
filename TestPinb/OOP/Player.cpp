/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Player.h"



//-------------------------------------------------------//
Player::Player()
//-------------------------------------------------------//
{
}

//-------------------------------------------------------//
Player::~Player()
//-------------------------------------------------------//
{
}


//-------------------------------------------------------//
void Player::Init(StageBase *stage)
//-------------------------------------------------------//
{
	this->m_Stage = stage;
	this->m_nBalls = MAX_BALLS;
	m_Score = 0;
	m_ExtraBall = false;
	m_Status = StatusPlayer::waiting;
}

