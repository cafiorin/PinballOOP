/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage2.h"
#include "Player.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"
#include "DropTarget.h"

//Stage 2: (E: the great project)
//1 - Take the 5 Droptargets
//2 - Take the INPUT_SW_TARGET_HIGHER Target
//3 - Take the ball in hole.

//-----------------------------------------------------------
Stage2::Stage2(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage2 Constructor");
	#endif

	m_DropTargetOk = false;
	m_TargetsHigher = false;

	m_LedsHole = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsHole->AddLed(LED_HOLE_B1);
	m_LedsHole->AddLed(LED_HOLE_B2);
	m_LedsHole->AddLed(LED_HOLE_A1, true);
	m_LedsHole->AddLed(LED_HOLE_A2);

	m_LedsTargetHigher = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_B1);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_B2);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_B3);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_A1, true);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_A2);
}

//-----------------------------------------------------------
Stage2::~Stage2()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage2 Destructor");
	#endif
}

//-----------------------------------------------------------
int Stage2::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage2::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);

	if (event == EVENT_DROPTARGETDOWN && 
		sender == m_PinballMaster->m_DropTarget5 &&
		!m_DropTargetOk) //Step 1
	{
		m_DropTargetOk = true;
		m_LedsTargetHigher->Start();
		return score;
	}

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == INPUT_SW_TARGET_HIGHER && m_DropTargetOk) //Step 2
		{
			m_TargetsHigher = true;
			m_LedsTargetHigher->End();
			m_LedsHole->Start();
			return score;
		}

		if (valueToSend == INPUT_SW_HOLE && m_TargetsHigher) //Step 3
		{
			m_LedsHole->End();
			score += SCORE_TARGET_STAGE;
			Finished();
			return score;
		}
		else
		{
			score += SCORE_DEFAULT;
		}
	}

	return score;
}

//-----------------------------------------------------------
void Stage2::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage2::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	ResetStage();
}

//-----------------------------------------------------------
void Stage2::ResetStage()
//-----------------------------------------------------------
{
	m_DropTargetOk = false;
	m_TargetsHigher = false;
	m_LedsHole->Disable();
	m_PinballMaster->m_DropTarget3->Reset();
	m_PinballMaster->m_DropTarget5->Reset();
	SetLedStage();
}
	

//-----------------------------------------------------------
void Stage2::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage2::Finished");
	#endif

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
