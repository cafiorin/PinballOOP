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

	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

	void IncrementTestValue();
	void DecrementTestValue();

	bool EventUpDownButton(PinballObject *sender, bool upButton);
	void StartTest(int event);
	void DoTest();
	void DoTestLed();
	void DoTestCoin();
	void DoTestOutput();
	void DoPlaySound(bool board);
	void DoSfxOnOff();

	void FinishTest();

protected:
	int m_MenuTest;
	int m_startTestValue;
	Timer *m_timerAuto;

};

#endif
