/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage1.h"
#include "Player.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"

//Stage 1: (E: the great project)
//1 - Take the 3 Droptargets
//2 - Take the 3 Targets
//3 - Take the ball in hole.

//-----------------------------------------------------------
Stage1::Stage1(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage1 Constructor");
	#endif

	m_DropTargetOk = false;
}

//-----------------------------------------------------------
Stage1::~Stage1()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage1 Destructor");
	#endif
}

//-----------------------------------------------------------
int Stage1::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage1::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);

	if (event == EVENT_DROPTARGETDOWN)
	{
		m_DropTargetOk = true;
		return true;
	}

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == INPUT_SW_HOLE) //Target Stage
		{
			score += SCORE_TARGET_STAGE;
			Finished();
		}
		else
		{
			score += SCORE_DEFAULT;
		}
	}

	return score;
}

//-----------------------------------------------------------
void Stage1::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage1::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	SetLedStage();
}

//-----------------------------------------------------------
void Stage1::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage1::Finished");
	#endif

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
