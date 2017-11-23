#include "SelfTest.h"
#include "PinballMaster.h"
#include "LedControl.h"
#include "Timer.h"
#include "Output.h"
#include "DefinesMp3.h"

//---------------------------------------------------------------------//
SelfTest::SelfTest(PinballMaster *pinball) : PinballObject("TEST",pinball)
//---------------------------------------------------------------------//
{
	m_Pinball = pinball;
	m_timerAuto = new Timer(100, "TimerAuto", pinball, this, TimerType::continuous);
}

//---------------------------------------------------------------------//
SelfTest::~SelfTest()
//---------------------------------------------------------------------//
{
	delete m_timerAuto;
}

//---------------------------------------------------------------------//
void SelfTest::IncrementTestValue()
//---------------------------------------------------------------------//
{
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
	}
}

//---------------------------------------------------------------------//
void SelfTest::DecrementTestValue()
//---------------------------------------------------------------------//
{
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
bool SelfTest::EventUpDownButton(PinballObject *sender, bool upButton)
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_LED_1BY1 || 
		m_MenuTest == EVENT_TEST_COIN_1BY1 ||
		m_MenuTest == EVENT_TEST_OUTPUTS_1BY1)
	{
		upButton ? IncrementTestValue() : DecrementTestValue();
	}

	DoTest();
	return false;
}

//---------------------------------------------------------------------//
void SelfTest::StartTest(int event)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::StartTest");
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
	Debug("SelfTest::DoTest");
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
	Debug("SelfTest::DoTestLed");
	#endif

	LedControl *ledControl = m_Pinball->GetLedControl();

	char szLed[5];
	sprintf(szLed, "%d", m_startTestValue);
	m_Pinball->printText("Led:", szLed, 0);

	if (ledControl->IsTurn(m_startTestValue))
	{
		ledControl->TurnOff(m_startTestValue);
	}
	else
	{
		ledControl->TurnOn(m_startTestValue);
	}
}

//---------------------------------------------------------------------//
void SelfTest::DoTestCoin()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::DoTestCoin");
	#endif


	char szCoin[5];
	sprintf(szCoin, "%d", m_startTestValue);
	m_Pinball->printText("Coin:", szCoin, 0);

	Output *pOutput = m_pinball->GetOutput(m_startTestValue + OUTPUT_COINS_INIT);
	if (pOutput != NULL)
	{
		pOutput->TurnOnByTimer(200);
	}
}

//---------------------------------------------------------------------//
void SelfTest::DoTestOutput()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::DoTestOutput");
	#endif

	char szOut[5];
	sprintf(szOut, "%d", m_startTestValue);
	m_Pinball->printText("Output", szOut, 0);

	Output *pOutput = m_pinball->GetOutput(m_startTestValue + OUTPUT_LOW_INIT);
	if (pOutput != NULL)
	{
		pOutput->TurnOnByTimer(1000);
	}
}


//---------------------------------------------------------------------//
void SelfTest::DoPlaySound(bool board)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::DoPlaySound");
	#endif
	if (board)
	{
		m_Pinball->playSong(MP3_EXTRABALL, true);
		m_Pinball->printText("Play", "board1", 0);
	}
	else
	{
		m_Pinball->sendMessageToAnotherArduino(ADDRESS_SLAVE, INIT_THEME);
		m_Pinball->printText("Play", "board2", 0);
	}
}


//---------------------------------------------------------------------//
void SelfTest::FinishTest()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::FinishTest");
	#endif

	m_Pinball->clearDisplay();

	switch (m_MenuTest)
	{
		case EVENT_TEST_LED_1BY1:
		case EVENT_TEST_LED_AUTO:
		{
			LedControl *ledControl = m_Pinball->GetLedControl();
			for (int i = 0; i < MAX_LEDS; i++)
			{
				ledControl->TurnOff(i);
			}
		}
		break;

	//TODO: other cases
	}
}

//---------------------------------------------------------------------//
bool SelfTest::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	// -- T I M E R  I S  O V E R --
	if (event == EVENT_TIMEISOVER)
	{
		DoTest();
		return true;
	}

	return false;
}
