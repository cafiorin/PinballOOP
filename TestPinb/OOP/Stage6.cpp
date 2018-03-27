/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage6.h"
#include "Player.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"
#include "DropTarget.h"
#include "DefinesMp3.h"
#include "KickoutHole.h"
#include "Timer.h"

#ifdef DOS
#include <cstdlib> // for srand, rand
#include <ctime>   // for time
#endif

//Stage 2: (E: the great project)
//1 - Take the 5 Droptargets
//2 - Take the 3 Droptargets
//3 - Take the INPUT_SW_HOLE Target
//4 - Take the Ramp
//5 - Take the ball in hole.

//-----------------------------------------------------------
Stage6::Stage6(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage6 Constructor");
	#endif

	#ifdef ARDUINOLIB
	m_FlagCurrent = random(MAX_FLAGS);
	#endif

	#ifdef DOS
	srand(time(0));
	m_FlagCurrent = rand() % MAX_FLAGS;
	#endif // DOS
	
	m_FlagCapturedCount = 0;
	m_TimerToCapture = new Timer(1000, "TimerCap", pinball, this, TimerType::continuous);

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
Stage6::~Stage6()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage6 Destructor");
	#endif
}

//---------------------------------------------------------------------//
bool Stage6::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("Stage6::NotifyEvent");
#endif

	// -- T I M E R  I S  O V E R --
	if (event == EVENT_TIMEISOVER)
	{
		m_FlagCapturedCount = 0;
		m_PinballMaster->playSong(MP3_TIMEISOVER);
		
		for (int i = 0; i < MAX_FLAGS; i++)
			m_Flags[i]->Disable();

		m_Flags[m_FlagCurrent]->EnableToCapture();
	}

	return false;
}


//-----------------------------------------------------------
int Stage6::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage6::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);

	if(valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
	{
		if (valueToSend == m_Flags[m_FlagCurrent]->GetNumber() && m_FlagCapturedCount < MAX_FLAGS)
		{
			m_PinballMaster->playSong(MP3_STAGESTEP);
			m_Flags[m_FlagCurrent]->Captured();
			m_FlagCapturedCount++;
			
			if (m_FlagCapturedCount >= MAX_FLAGS)
			{
				m_LedsHole->Start();
			}
			else
			{
				do
				{
					#ifdef ARDUINOLIB
					m_FlagCurrent = random(MAX_FLAGS);
					#endif

					#ifdef DOS
					m_FlagCurrent = rand() % MAX_FLAGS;
					#endif // DOS

				} while (m_Flags[m_FlagCurrent]->IsCaptured());

				m_Flags[m_FlagCurrent]->EnableToCapture();
			}
		}

		if (valueToSend == INPUT_SW_HOLE && (m_FlagCurrent >= MAX_FLAGS))
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
void Stage6::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage6::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	ResetStage();
}

//-----------------------------------------------------------
void Stage6::ResetStage()
//-----------------------------------------------------------
{
	for (int i = 0; i < MAX_FLAGS; i++)
	{
		m_Flags[i]->Disable();
	}
	m_FlagCurrent = 0;
	m_Flags[m_FlagCurrent]->EnableToCapture();
	m_LedsHole->Disable();

	DropTarget* dt3 = m_PinballMaster->GetDropTarget3();
	if(dt3 != NULL)
		dt3->Reset();

	DropTarget *dt5 = m_PinballMaster->GetDropTarget5();
	if(dt5 != NULL)
		dt5->Reset();
	SetLedStage();
	m_TimerToCapture->Start();
}
	

//-----------------------------------------------------------
void Stage6::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage6::Finished");
	#endif

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
