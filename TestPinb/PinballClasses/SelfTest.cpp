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


//---------------------------------------------------------------------//
SelfTest::SelfTest(PinballMachine* pinballMachine)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SelfTest Constructor"));
	#endif
	m_Pinball = pinballMachine;
	m_timerAuto = new NewTimer(1000, NewTimerType::continuous, this);
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
	#ifdef DEBUGMESSAGES
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
			DisplayInput(0);
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


	char szCoin[5];
	sprintf(szCoin, "%d", m_startTestValue + OUTPUT_COINS_INIT);
	m_Pinball->printText("Coin", szCoin, 0);

	BitOutput *pOutput = m_Pinball->GetOutputsHighVoltage()->GetOuput(m_startTestValue + OUTPUT_COINS_INIT);
	if (pOutput != NULL)
	{
		pOutput->TurnOn();
	}
}

//---------------------------------------------------------------------//
void SelfTest::DoTestOutput()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SelfTest::DoTestOutput"));
	#endif

	BitOutput* pOutput = NULL;
	while (pOutput == NULL)
	{
		pOutput = m_Pinball->GetOutputsLowVoltage()->GetOuput(m_startTestValue + OUTPUT_LOW_INIT);
		if (pOutput == NULL)
		{
			IncrementTestValue();
		}
	}

	if (pOutput != NULL)
	{
	  char szOut[5];
	  sprintf(szOut, "%d", pOutput->GetPortNumber());
	  m_Pinball->printText("Output", szOut, 0);
		
	  pOutput->TurnOnByTimer(1000);
	}
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
		char szOut[15];
		sprintf(szOut, "In%d : %d", pInput->GetPortNumber(), pInput->GetInput());
		m_Pinball->printText("Input", szOut, 0);
	}
}

//---------------------------------------------------------------------//
void SelfTest::DisplayInput(byte valueToSend)
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_INPUTS_AUTO)
	{
		#ifdef DEBUGMESSAGES
		Logger::LogMessage(F("SelfTest::EventToInput"));
		#endif

		bool values[8];
		byte bytes[6];

		byte j = 0, z = 0;
		for (byte i = INPUT_TEST_INIT; i <= INPUT_TEST_FINISH; i++)
		{
			bool value = false;
			BitInput* pInput = m_Pinball->GetMuxInputs()->GetInput(i);
			if (pInput != NULL)
			{
				value = pInput->GetInput();
			}
			values[j] = value;
			j++;
			if (j == 8)
			{
				j = 0;
				bytes[z] = ToByte(values);
				z++;
			}
		}

		BitInput* pInput = m_Pinball->GetMuxInputs()->GetInput(valueToSend);
		bool turnOn = false;
		if (pInput != NULL)
		{
			turnOn = pInput->GetInput();
		}

		char szOut[15];
		sprintf(szOut, "In%d : %d", valueToSend, turnOn);

		char szHexa[20];
		sprintf(szHexa, "%02x%02x%02x%02x%02x%02x", bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5]);

		m_Pinball->printText(szHexa, szOut, 0);

	}

}

//---------------------------------------------------------------------//
void SelfTest::EventToInput(byte valueToSend)
//---------------------------------------------------------------------//
{
	DisplayInput(valueToSend);
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
		m_Pinball->printText("Play", "board1", 0);
	}
	else
	{
		//TODO : m_Pinball->sendMessageToAnotherArduino(ADDRESS_SLAVE, COMM_TEST_SOUND);
		m_Pinball->printText("Play", "board2", 0);
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
void SelfTest::onNotifySubject(EventType event, byte value)
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
void SelfTest::Loop()
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_INPUTS_1BY1)
	{
		DoTest();
	}
}
