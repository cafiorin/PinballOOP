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

class SelfTest : public PinballObject
{
public:
	SelfTest(PinballMaster *pinball);
	virtual ~SelfTest();

	virtual bool NotifyEvent(Object *sender, Event *event);

	void IncrementTestValue();
	void DecrementTestValue();

	bool EventUpDownButton(PinballObject *sender, bool upButton);
	void StartTest(uint8_t event);
	void DoTest();
	void DoTestLed();
	void DoTestCoin();
	void DoTestOutput();
	void DoPlaySound(bool board);
	void DoSfxOnOff();

	void FinishTest();

protected:
	uint8_t m_MenuTest;
	uint8_t m_startTestValue;
	Timer *m_timerAuto;

};

#endif
