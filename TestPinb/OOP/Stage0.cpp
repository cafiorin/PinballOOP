#include "defines.h"
#include "Stage0.h"
#include "Player.h"
#include "SequencerLeds.h"

//Stage Qualify to race
//Target : Take ball in hole

//-----------------------------------------------------------
Stage0::Stage0(PinballMaster *pinball,int number):StageBase(pinball,number)
//-----------------------------------------------------------
{
	m_LedsStage = new SequencerLeds(pinball, SequencerType::turnOn1by1, 300);
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
	m_LedsTarget = new SequencerLeds(pinball, SequencerType::turnOn1by1, 300);
	m_LedsTarget->AddLed(LED_HOLE_CIRCLE1);
	m_LedsTarget->AddLed(LED_HOLE_CIRCLE2);
	m_LedsTarget->AddLed(LED_HOLE_ARROW11,true);
	m_LedsTarget->AddLed(LED_HOLE_ARROW12);
}

//-----------------------------------------------------------
Stage0::~Stage0()
//-----------------------------------------------------------
{
	delete m_LedsStage;
	delete m_LedsTarget;
}

//-----------------------------------------------------------
bool Stage0::Init()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("Stage0::Init");
	#endif

	return true;
}

//-----------------------------------------------------------
bool Stage0::Loop(int value)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("Stage0::Loop");
	#endif
	return false;
}

//-----------------------------------------------------------
int Stage0::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("Stage0::PlayfieldEvent");
	#endif

	int score = StageBase::PlayfieldEvent(sender,event,valueToSend);

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
