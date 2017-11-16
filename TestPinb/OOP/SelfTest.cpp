#include "SelfTest.h"
#include "PinballMaster.h"
#include "LedControl.h"

//---------------------------------------------------------------------//
SelfTest::SelfTest(PinballMaster *pinball) : PinballObject("TEST",pinball)
//---------------------------------------------------------------------//
{
	m_Pinball = pinball;
}

//---------------------------------------------------------------------//
SelfTest::~SelfTest()
//---------------------------------------------------------------------//
{
}

//---------------------------------------------------------------------//
bool SelfTest::EventUpDownButton(PinballObject *sender, bool upButton)
//---------------------------------------------------------------------//
{
	if (m_MenuTest == EVENT_TEST_LED_1BY1)
	{
		if (upButton)
			m_startTestValue++;
		else
			m_startTestValue--;

		if (m_startTestValue < 0)
			m_startTestValue = MAX_LEDS;

		if (m_startTestValue >= MAX_LEDS)
			m_startTestValue = 0;

		LoopTest();
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
	LoopTest();
}

//---------------------------------------------------------------------//
void SelfTest::LoopTest()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SelfTest::LoopTest");
	#endif

	switch (m_MenuTest)
	{
	case EVENT_TEST_LED_1BY1:
	{
		LedControl *ledControl = m_Pinball->GetLedControl();

		char szLed[3];
		sprintf(szLed, "%d", m_startTestValue);
		m_Pinball->printText("Led:", szLed, 0);
		ledControl->TurnOn(m_startTestValue);
		if (m_startTestValue - 1 > 0)
		{
			ledControl->TurnOff(m_startTestValue);
		}
		ledControl->TurnOn(m_startTestValue);
	}
	break;

	case EVENT_TEST_LED_AUTO:
		//TODO:
		break;

	//TODO: other cases
	}
}




