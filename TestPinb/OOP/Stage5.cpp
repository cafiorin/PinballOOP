/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "Stage5.h"
#include "Player.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"
#include "DropTarget.h"
#include "DefinesMp3.h"
#include "KickoutHole.h"

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
Stage5::Stage5(PinballMaster *pinball,uint8_t number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage5 Constructor");
	#endif

	#ifdef ARDUINOLIB
	m_FlagCurrent = random(MAX_FLAGS);
	#endif

	#ifdef DOS
	srand(time(0));
	m_FlagCurrent = rand() % MAX_FLAGS;
	#endif // DOS
	
	m_FlagCapturedCount = 0;

	//TARGET_GREEN1
	uint8_t count = 0;
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
Stage5::~Stage5()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Stage5 Destructor");
	#endif
}

//-----------------------------------------------------------
uint8_t Stage5::PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage5::PlayfieldEvent");
	#endif

	uint8_t score = StageBase::PlayfieldEvent(sender,event,valueToSend);

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
void Stage5::RestartPlayer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage5::RestartPlayer");
	#endif

	StageBase::RestartPlayer();
	ResetStage();
}

//-----------------------------------------------------------
void Stage5::ResetStage()
//-----------------------------------------------------------
{
	for (uint8_t i = 0; i < MAX_FLAGS; i++)
	{
		m_Flags[i]->Disable();
	}
	m_FlagCurrent = 0;
	m_Flags[m_FlagCurrent]->EnableToCapture();
	m_LedsHole->Disable();

	DropTarget* dt3 = m_PinballMaster->GetDropTarget3();
	if (dt3 != NULL)
		dt3->Reset();

	DropTarget *dt5 = m_PinballMaster->GetDropTarget5();
	if (dt5 != NULL)
		dt5->Reset();
	SetLedStage();
}
	

//-----------------------------------------------------------
void Stage5::Finished()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage5::Finished");
	#endif

	if (m_currentPlayer != NULL)
	{
		m_currentPlayer->SetNextStage();
	}
}
