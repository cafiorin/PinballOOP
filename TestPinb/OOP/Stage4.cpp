/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage4.h"
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
Stage4::Stage4(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage4 Constructor");
	#endif

	m_FlagCount = 0;

	//TARGET_GREEN1
	int count = 0;
	m_Flags[count] = new Flag(INPUT_SW_TARGET_GREEN1);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_GREEN1);

	count++;
	//TARGET_RED1
	m_Flags[count] = new Flag(INPUT_SW_TARGET_RED1);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_RED1);

	count++;
	//TARGET_YELLOW1
	m_Flags[count] = new Flag(INPUT_SW_TARGET_YELLOW1);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_YELLOW1_B1);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_YELLOW1_B2);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_YELLOW1_A1,true);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_YELLOW1_A2);

	count++;
	//TARGET_RED2
	m_Flags[count] = new Flag(INPUT_SW_TARGET_RED2);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_RED2);

	count++;
	//TARGET_YELLOW2
	m_Flags[count] = new Flag(INPUT_SW_TARGET_YELLOW2);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_YELLOW2);


	//TARGET_GREEN2
	count++;
	m_Flags[count] = new Flag(INPUT_SW_TARGET_GREEN2);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_GREEN2);

	//TARGET_HIGHER
	count++;
	m_Flags[count] = new Flag(INPUT_SW_HOLE);
	m_Flags[count]->m_Leds = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_HIGHER_B1);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_HIGHER_B2);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_HIGHER_B3);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_HIGHER_A1, true);
	m_Flags[count]->m_Leds->AddLed(LED_TARGET_HIGHER_A2);

	m_LedsHole = new SequencerLeds(pinball, SequencerType::turnOnAndturnOff_1by1, 300);
	m_LedsHole->AddLed(LED_HOLE_B1);
	m_LedsHole->AddLed(LED_HOLE_B2);
	m_LedsHole->AddLed(LED_HOLE_A1, true);
	m_LedsHole->AddLed(LED_HOLE_A2);

}

//-----------------------------------------------------------
Stage4::~Stage4()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage4 Destructor");
	#endif
}

//-----------------------------------------------------------
int Stage4::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage4::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == m_Flags[m_FlagCount]->GetNumber() && m_FlagCount < MAX_FLAGS)
		{
			m_PinballMaster->playSong(MP3_STAGESTEP);
			m_Flags[m_FlagCount]->Captured();
			m_FlagCount++;
			if (m_FlagCount >= MAX_FLAGS)
			{
				m_LedsHole->Start();
			}
			else
			{
				m_Flags[m_FlagCount]->EnableToCapture();
			}
		}

		if (valueToSend == INPUT_SW_HOLE && (m_FlagCount >= MAX_FLAGS))
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
void Stage4::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage4::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	ResetStage();
}

//-----------------------------------------------------------
void Stage4::ResetStage()
//-----------------------------------------------------------
{
	for (int i = 0; i < MAX_FLAGS; i++)
	{
		m_Flags[i]->Disable();
	}
	m_FlagCount = 0;
	m_Flags[m_FlagCount]->EnableToCapture();
	m_LedsHole->Disable();

	m_PinballMaster->m_DropTarget3->Reset();
	m_PinballMaster->m_DropTarget5->Reset();
	SetLedStage();
}
	

//-----------------------------------------------------------
void Stage4::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage4::Finished");
	#endif

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
