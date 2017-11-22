#include "SelfTest.h"
#include "PinballMaster.h"
#include "LedControl.h"
#include "Timer.h"

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
}

//---------------------------------------------------------------------//
void SelfTest::IncrementTestValue()
//---------------------------------------------------------------------//
{
	m_startTestValue++;
	if (m_startTestValue >= MAX_LEDS)
		m_startTestValue = 0;

}

//---------------------------------------------------------------------//
void SelfTest::DecrementTestValue()
//---------------------------------------------------------------------//
{
	m_startTestValue--;
	if (m_startTestValue < 0)
		m_startTestValue = MAX_LEDS-1;

}


//---------------------------------------------------------------------//
bool SelfTest::EventUpDownButton(PinballObject *sender, bool upButton)
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_LED_1BY1)
	{
		upButton ? IncrementTestValue() : DecrementTestValue();
		DoTest();
	}

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
		LedControl *ledControl = m_Pinball->GetLedControl();

		char szLed[3];
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
	break;

	case EVENT_TEST_LED_AUTO:
		m_timerAuto->Start();

		LedControl *ledControl = m_Pinball->GetLedControl();

		char szLed[3];
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

		IncrementTestValue();
		break;

	//TODO: other cases
	}
}

//---------------------------------------------------------------------//
void SelfTest::FinishTest()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::FinishTest");
	#endif


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
		return TimerIsOver(sender);
	}

	return false;
}


//---------------------------------------------------------------------//
bool SelfTest::TimerIsOver(PinballObject *sender)
//---------------------------------------------------------------------//
{
	if (sender == m_timerAuto)
	{
		#ifdef DEBUGMESSAGES
		Debug("...Timer is over game over");
		#endif
		DoTest();
		return true;
	}

	return false;
}


