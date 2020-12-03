/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SelfTest.h"
#include "NewTimer.h"

#include "BitOutput.h"
#include "BitInput.h"

#include "MultiplexInputs.h"
#include "LatchOutputs.h"

#include "DefinesMp3.h"
#include "LedControl.h"
#include "Utils.h"

#include "Observer.h"
#include "PinballMachine.h"
#include "Logger.h"
#include "Runnable.h"


//---------------------------------------------------------------------//
SelfTest::SelfTest(PinballMachine* pinballMachine) : Runnable()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SelfTest Constructor"));
	#endif
	m_Pinball = pinballMachine;
	m_timerAuto = new NewTimer(1000, NewTimerType::continuous, this);
	strcpy(m_szOut, "");
	strcpy(m_szHexa, "");
	m_lastIndexHigh = 0;
}

//---------------------------------------------------------------------//
SelfTest::~SelfTest()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SelfTest Destructor"));
	#endif

	delete m_timerAuto; 
}

//---------------------------------------------------------------------//
void SelfTest::IncrementTestValue()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest IncrementTestValue"));
	#endif

	m_startTestValue++;

	switch (m_MenuTest)
	{
		case EVENT_TEST_LED_1BY1:
		case EVENT_TEST_LED_AUTO:
			{
				if (m_startTestValue >= MAX_LEDS)
					m_startTestValue = 0;
			}
			break;

		case EVENT_TEST_COIN_1BY1:
		case EVENT_TEST_COIN_AUTO:
		{
			if (m_startTestValue >= OUTPUT_COINS_FINISH - OUTPUT_COINS_INIT + 1)
				m_startTestValue = 0;
		}
		break;

		case EVENT_TEST_OUTPUTS_1BY1:
		case EVENT_TEST_OUTPUTS_AUTO:
		{
			if (m_startTestValue >= OUTPUT_LOW_FINISH - OUTPUT_LOW_INIT + 1)
				m_startTestValue = 0;
		}
		break;

		case EVENT_TEST_INPUTS_1BY1:
		case EVENT_TEST_INPUTS_AUTO:
		{
			if (m_startTestValue >= INPUT_PLAYFIELD_FINISH - INPUT_PLAYFIELD_INIT + 1)
				m_startTestValue = 0;
		}
		break;
	}
}

//---------------------------------------------------------------------//
void SelfTest::DecrementTestValue()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest DecrementTestValue"));
	#endif

	m_startTestValue--;

	switch (m_MenuTest)
	{
		case EVENT_TEST_LED_1BY1:
		case EVENT_TEST_LED_AUTO:
		{
			if (m_startTestValue < 0)
				m_startTestValue = MAX_LEDS - 1;
		}
		break;

		case EVENT_TEST_COIN_1BY1:
		case EVENT_TEST_COIN_AUTO:
		{
			if (m_startTestValue < 0)
				m_startTestValue = OUTPUT_COINS_FINISH - OUTPUT_COINS_INIT;
		}
		break;

		case EVENT_TEST_OUTPUTS_1BY1:
		case EVENT_TEST_OUTPUTS_AUTO:
		{
			if (m_startTestValue < 0)
				m_startTestValue = OUTPUT_LOW_FINISH - OUTPUT_LOW_INIT;
		}
		break;

	}
}


//---------------------------------------------------------------------//
bool SelfTest::EventUpDownButton(bool upButton)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest EventUpDownButton"));
	#endif


	if (m_MenuTest == EVENT_TEST_LED_1BY1 || 
		m_MenuTest == EVENT_TEST_COIN_1BY1 ||
		m_MenuTest == EVENT_TEST_OUTPUTS_1BY1 ||
		m_MenuTest == EVENT_TEST_INPUTS_1BY1)
	{
		upButton ? IncrementTestValue() : DecrementTestValue();
	}

	DoTest();
	return false;
}

//---------------------------------------------------------------------//
void SelfTest::StartTest(byte event)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::StartTest"));
	#endif

	m_MenuTest = event;
	m_startTestValue = 0;
	DoTest();
}

//---------------------------------------------------------------------//
void SelfTest::DoTest()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Logger::LogMessage(F("SelfTest::DoTest"));
	#endif

	switch (m_MenuTest)
	{
		case EVENT_TEST_LED_1BY1:
		{
			DoTestLed();
		}
		break;

		case EVENT_TEST_LED_AUTO:
		{
			m_timerAuto->Start();
			DoTestLed();
			IncrementTestValue();
		}
		break;
	
		case EVENT_TEST_COIN_1BY1:
		{
			DoTestCoin();
		}
		break;

		case EVENT_TEST_COIN_AUTO:
		{
			m_timerAuto->Start();
			DoTestCoin();
			IncrementTestValue();
		}
		break;

		case EVENT_TEST_OUTPUTS_1BY1:
		{
			DoTestOutput();
		}
		break;

		case EVENT_TEST_OUTPUTS_AUTO:
		{
			m_timerAuto->Start();
			DoTestOutput();
			IncrementTestValue();
		}
		break;

		case EVENT_TEST_INPUTS_1BY1:
		{
			DoTestInput();
		}
		break;

		case EVENT_TEST_INPUTS_AUTO:
		{
			DisplayInput();
		}
		break;


		case EVENT_TEST_SOUND_BOARD1:
		{
			DoPlaySound(true);
		}
		break;

		case EVENT_TEST_SOUND_BOARD2:
		{
			DoPlaySound(false);
		}
		break;

		case EVENT_TEST_SFX_ONOFF:
		{
			DoSfxOnOff();
		}
		break;
	}
}

//---------------------------------------------------------------------//
void SelfTest::DoSfxOnOff()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest DoSfxOnOff"));
	#endif


	if (m_Pinball->IsEnabledSFX())
	{
		m_Pinball->EnableSFX(false);
		m_Pinball->printText("SFX", "Disable", 0);
	}
	else
	{
		m_Pinball->EnableSFX(true);
		m_Pinball->printText("SFX", "Enable", 0);
	}
}


//---------------------------------------------------------------------//
void SelfTest::DoTestLed()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::DoTestLed"));
	#endif

	char szLed[5];
	sprintf(szLed, "%d", m_startTestValue);
	m_Pinball->printText("Led", szLed, 0);

	LedControl *ledControl = m_Pinball->GetLedControl();
	if (ledControl != NULL)
	{
		if (ledControl->IsTurn(m_startTestValue))
		{
			ledControl->TurnOff(m_startTestValue);
		}
		else
		{
			ledControl->TurnOn(m_startTestValue);
		}
	}
}

//---------------------------------------------------------------------//
void SelfTest::DoTestCoin()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::DoTestCoin"));
	#endif

	byte coinToTest = m_startTestValue + OUTPUT_COINS_INIT;

	char szCoin[5];
	sprintf(szCoin, "%d", coinToTest);
	m_Pinball->printText("Coin", szCoin, 0);

	m_Pinball->GetOutputsHighVoltage()->GetOuput(coinToTest)->Pulse(500);
}

//---------------------------------------------------------------------//
void SelfTest::DoTestOutput()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::DoTestOutput"));
	#endif

	BitOutput* pOutput = m_Pinball->GetOutputsLowVoltage()->GetOuput(m_startTestValue + OUTPUT_LOW_INIT);
	char szOut[5];
	sprintf(szOut, "%d", pOutput->GetPortNumber());
	m_Pinball->printText("Output", szOut, 0);
		
	pOutput->TurnOnByTimer(1000);
}

//---------------------------------------------------------------------//
void SelfTest::DoTestInput()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::DoTestInput"));
	#endif
	
	BitInput* pInput = m_Pinball->GetMuxInputs()->GetInput(m_startTestValue + INPUT_PLAYFIELD_INIT);
	if (pInput != NULL)
	{
		char szInputOut[15];
		sprintf(szInputOut, "In %d", pInput->GetPortNumber());

		char szOut[15];
		sprintf(szOut, "%s", (pInput->GetInput()?"true":"false"));
		m_Pinball->printText(szInputOut, szOut, 0);
	}
}

//---------------------------------------------------------------------//
void SelfTest::DisplayInput()
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_INPUTS_AUTO)
	{
		#ifdef DEBUGMESSAGESLOOP
		Logger::LogMessage(F("SelfTest::DisplayInput"));
		#endif

		bool values[8];
		byte bytes[6];

		byte indexValues = 0, indexBytes = 0;
		for (byte index = INPUT_TEST_INIT; index <= INPUT_TEST_FINISH; index++)
		{
			values[indexValues] = m_Pinball->GetMuxInputs()->GetInput(index)->GetInput();
			if (values[indexValues] != values[indexValues])
			{
				m_lastIndexHigh = index;
			}
			indexValues++;
			if (indexValues == 8)
			{
				indexValues = 0;
				bytes[indexBytes] = ToByte(values);
				indexBytes++;
			}
		}

		bool turnOn = m_Pinball->GetMuxInputs()->GetInput(m_lastIndexHigh)->GetInput();

		char szOut[15];
		sprintf(szOut, "In%d : %d", m_lastIndexHigh, turnOn);

		char szHexa[20];
		sprintf(szHexa, "%02x%02x%02x%02x%02x%02x", bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5]);
		
		if (strcmp(szHexa, m_szHexa) || strcmp(szOut, m_szOut))
		{
			strcpy(m_szHexa, szHexa);
			strcpy(m_szOut, szOut);

			m_Pinball->printText(szHexa, szOut, 0);
		}
	}
}

//---------------------------------------------------------------------//
void SelfTest::DoPlaySound(bool board)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::DoPlaySound"));
	#endif

	if (board)
	{
		m_Pinball->playSong(MP3_TESTSOUND);
		m_Pinball->printText("Playing", "Board1", 0);
		delay(1000);
		m_Pinball->printText("Sound", "Board1", 0);
	}
	else
	{
		m_Pinball->playSong(MP3_TESTSOUND,true);
		m_Pinball->printText("Playing", "Board2", 0);
		delay(1000);
		m_Pinball->printText("Sound", "Board2", 0);
	}
}


//---------------------------------------------------------------------//
void SelfTest::FinishTest()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::FinishTest"));
	#endif

	m_Pinball->clearDisplay();

	switch (m_MenuTest)
	{
		case EVENT_TEST_LED_1BY1:
		case EVENT_TEST_LED_AUTO:
		{
			LedControl *ledControl = m_Pinball->GetLedControl();
			if (ledControl != NULL)
			{
				for (byte i = 0; i < MAX_LEDS; i++)
				{
					ledControl->TurnOff(i);
				}
			}
		}
		break;
	}
}

//---------------------------------------------------------------------//
void SelfTest::onNotifySubject(EventType event, byte /*value*/)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::NotifyEvent"));
	#endif

	// -- T I M E R  I S  O V E R --
	if (event == EventType::TimeIsOver)
	{
		DoTest();
	}
}

//---------------------------------------------------------------------//
void SelfTest::loop()
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_INPUTS_1BY1 ||
		m_MenuTest == EVENT_TEST_INPUTS_AUTO)
	{
		DoTest();
	}
}
