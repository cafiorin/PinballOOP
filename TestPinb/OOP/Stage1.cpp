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
#include "DropTarget.h"
#include "DefinesMp3.h"

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
	m_Targets[0] = false;
	m_Targets[1] = false;
	m_Targets[2] = false;
	m_LedsHole = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsHole->AddLed(LED_HOLE_B1);
	m_LedsHole->AddLed(LED_HOLE_B2);
	m_LedsHole->AddLed(LED_HOLE_A1, true);
	m_LedsHole->AddLed(LED_HOLE_A2);
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

	if (event == EVENT_DROPTARGETDOWN && sender == m_PinballMaster->m_DropTarget3)
	{
		m_DropTargetOk = true;
		m_PinballMaster->playSong(MP3_STAGESTEP);
		return score;
	}

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == INPUT_SW_TARGET_RED2 ||
			valueToSend == INPUT_SW_TARGET_GREEN2 || 
			valueToSend == INPUT_SW_TARGET_YELLOW2)
		{
			m_Targets[INPUT_SW_TARGET_RED2 - valueToSend] = true;
		}

		if (valueToSend == INPUT_SW_HOLE && m_LedsHole->IsEnabled()) //Target Stage
		{
			score += SCORE_TARGET_STAGE;
			Finished();
		}
		else
		{
			score += SCORE_DEFAULT;
		}
	}

	if (m_Targets[0] && m_Targets[1] && m_Targets[2] && m_DropTargetOk && !m_LedsHole->IsEnabled())
	{
		m_LedsHole->Start();
		m_PinballMaster->playSong(MP3_STAGESTEP);
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
	ResetStage();
}

//-----------------------------------------------------------
void Stage1::ResetStage()
//-----------------------------------------------------------
{
	m_DropTargetOk = false;
	m_Targets[0] = false;
	m_Targets[1] = false;
	m_Targets[2] = false;
	m_LedsHole->Disable();
	m_PinballMaster->m_DropTarget3->Reset();
	m_PinballMaster->m_DropTarget5->Reset();
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
