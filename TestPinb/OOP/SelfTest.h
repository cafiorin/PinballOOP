/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SelfTest__INCLUDED_
#define SelfTest__INCLUDED_

#include "defines.h"
#include "pinballobject.h"

class PinballMaster;
class Timer;

class SelfTest : public Object
{
public:
	SelfTest();
	virtual ~SelfTest();

	virtual bool NotifyEvent(Object *sender, uint8_t event, uint8_t value);

	void IncrementTestValue();
	void DecrementTestValue();

	bool EventUpDownButton(Object *sender, bool upButton);
	void StartTest(uint8_t event);
	void DoTest();
	void DoTestLed();
	void DoTestCoin();
	void DoTestOutput();
	void DoPlaySound(bool board);
	void DoSfxOnOff();

	void FinishTest();
	void Loop();

protected:
	uint8_t m_MenuTest;
	uint8_t m_startTestValue;
	Timer *m_timerAuto;

};

#endif
