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
#include "DefinesMp3.h"

//Stage 2: (E: the great project)
//1 - Take the 5 Droptargets
//2 - Take the INPUT_SW_HOLE Target
//3 - Take the ball in hole.

//-----------------------------------------------------------
Stage2::Stage2(PinballMaster *pinball,uint8_t number):StageBase(pinball,number)
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
uint8_t Stage2::PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage2::PlayfieldEvent");
	#endif

	uint8_t score = StageBase::PlayfieldEvent(sender,event,valueToSend);

	DropTarget *dt5 = m_PinballMaster->GetDropTarget5();
	if (event == EVENT_DROPTARGETDOWN && 
		sender == dt5 && dt5 != NULL &&
		!m_DropTargetOk) //Step 1
	{
		m_DropTargetOk = true;
		m_LedsTargetHigher->Start();
		m_PinballMaster->playSong(MP3_STAGESTEP);
		return score;
	}

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == INPUT_SW_HOLE && m_DropTargetOk) //Step 2
		{
			m_TargetsHigher = true;
			m_LedsTargetHigher->End();
			m_LedsHole->Start();
			m_PinballMaster->playSong(MP3_STAGESTEP);
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

	DropTarget* dt3 = m_PinballMaster->GetDropTarget3();
	DropTarget *dt5 = m_PinballMaster->GetDropTarget5();
	if (dt3 != NULL)
		dt3->Reset();
	if (dt5 != NULL)
		dt5->Reset();

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
