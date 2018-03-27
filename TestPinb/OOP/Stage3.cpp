/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage3.h"
#include "Player.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"
#include "DropTarget.h"
#include "DefinesMp3.h"

//Stage 2: (E: the great project)
//1 - Take the 5 Droptargets
//2 - Take the 3 Droptargets
//3 - Take the INPUT_SW_HOLE Target
//4 - Take the Ramp
//5 - Take the ball in hole.

//-----------------------------------------------------------
Stage3::Stage3(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage3 Constructor");
	#endif

	m_DropTarget5 = false;
	m_DropTarget3 = false;
	m_TargetsHigher = false;
	m_RampOut2 = false;

	m_LedsHole = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsHole->AddLed(LED_HOLE_B1);
	m_LedsHole->AddLed(LED_HOLE_B2);
	m_LedsHole->AddLed(LED_HOLE_A1, true);
	m_LedsHole->AddLed(LED_HOLE_A2);

	m_LedsRamp = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsRamp->AddLed(LED_RAMP_B1);
	m_LedsRamp->AddLed(LED_RAMP_B2);
	m_LedsRamp->AddLed(LED_RAMP_A1, true);
	m_LedsRamp->AddLed(LED_RAMP_A2);

	m_LedsTargetHigher = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_B1);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_B2);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_B3);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_A1, true);
	m_LedsTargetHigher->AddLed(LED_TARGET_HIGHER_A2);
}

//-----------------------------------------------------------
Stage3::~Stage3()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage3 Destructor");
	#endif
}

//-----------------------------------------------------------
int Stage3::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage3::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);

	DropTarget* dt3 = m_PinballMaster->GetDropTarget3();
	DropTarget *dt5 = m_PinballMaster->GetDropTarget5();

	if (event == EVENT_DROPTARGETDOWN && 
		sender == dt5 &&
		!m_DropTarget5) //Step 1
	{
		if(dt3 != NULL)
			dt3->Reset();
		m_DropTarget5 = true;
		m_PinballMaster->playSong(MP3_STAGESTEP);
		return score;
	}

	if (event == EVENT_DROPTARGETDOWN &&
		sender == dt3 &&
		!m_DropTarget3 && m_DropTarget5) //Step2
	{
		m_DropTarget3 = true;
		m_LedsTargetHigher->Start();
		m_PinballMaster->playSong(MP3_STAGESTEP);
		return score;
	}

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == INPUT_SW_HOLE &&
			m_DropTarget3) //Step3
		{
			m_TargetsHigher = true;
			m_LedsTargetHigher->End();
			m_LedsRamp->Start();
			m_PinballMaster->playSong(MP3_STAGESTEP);
		}

		if (valueToSend == INPUT_SW_RAMP_OUT2 &&
			m_TargetsHigher) //Step4
		{
			m_RampOut2 = true;
			m_LedsRamp->End();
			m_LedsHole->Start();
			m_PinballMaster->playSong(MP3_STAGESTEP);
		}

		if (valueToSend == INPUT_SW_HOLE && m_RampOut2) //Step5
		{
			m_LedsHole->End();
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
void Stage3::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage3::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	ResetStage();
}

//-----------------------------------------------------------
void Stage3::ResetStage()
//-----------------------------------------------------------
{
	m_DropTarget5 = false;
	m_DropTarget3 = false;
	m_TargetsHigher = false;
	m_RampOut2 = false;

	m_LedsHole->Disable();
	m_LedsTargetHigher->Disable();
	m_LedsRamp->Disable();

	DropTarget* dt3 = m_PinballMaster->GetDropTarget3();
	if (dt3 != NULL)
		dt3->Reset();

	DropTarget *dt5 = m_PinballMaster->GetDropTarget5();
	if (dt5 != NULL)
		dt5->Reset();

	SetLedStage();
}
	

//-----------------------------------------------------------
void Stage3::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage3::Finished");
	#endif

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
