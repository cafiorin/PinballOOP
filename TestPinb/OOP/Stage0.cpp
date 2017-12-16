/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage0.h"
#include "Player.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"
#include "DropTarget.h"
#include "DefinesMp3.h"

//Stage Qualify to race
//Target : Take ball in hole

//-----------------------------------------------------------
Stage0::Stage0(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage0 Constructor");
	#endif

	m_LedsStage = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsStage->AddLed(LED_STAGE11, true);
	m_LedsStage->AddLed(LED_STAGE12);

	m_LedsStage->AddLed(LED_STAGE21, true);
	m_LedsStage->AddLed(LED_STAGE22);

	m_LedsStage->AddLed(LED_STAGE31, true);
	m_LedsStage->AddLed(LED_STAGE32);

	m_LedsStage->AddLed(LED_STAGE41, true);
	m_LedsStage->AddLed(LED_STAGE42);

	m_LedsStage->AddLed(LED_STAGE51, true);
	m_LedsStage->AddLed(LED_STAGE52);

	// Target
	m_LedsTarget = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsTarget->AddLed(LED_HOLE_B1);
	m_LedsTarget->AddLed(LED_HOLE_B2);
	m_LedsTarget->AddLed(LED_HOLE_A1,true);
	m_LedsTarget->AddLed(LED_HOLE_A2);
}

//-----------------------------------------------------------
Stage0::~Stage0()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage0 Destructor");
	#endif

	delete m_LedsStage;
	delete m_LedsTarget;
}

//-----------------------------------------------------------
int Stage0::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage0::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);
	
	if (event == EVENT_DROPTARGETDOWN)
	{
		if(sender == m_PinballMaster->m_DropTarget3)
			m_PinballMaster->m_DropTarget3->Reset();
		else
			m_PinballMaster->m_DropTarget5->Reset();
		return score;
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
void Stage0::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage0::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	m_LedsStage->Start();
	m_LedsTarget->Start();
}

//-----------------------------------------------------------
void Stage0::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage0::Finished");
	#endif

	m_LedsStage->End();
	m_LedsTarget->End();

	m_LedsStage->Disable();
	m_LedsTarget->Disable();

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
