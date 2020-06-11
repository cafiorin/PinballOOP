/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SelfTest__INCLUDED_
#define SelfTest__INCLUDED_

#include "defines.h"
#include "Observer.h"
#include "Runnable.h"

class NewTimer;
class PinballMachine;

class SelfTest : Observer, Runnable
{
public:
	SelfTest(PinballMachine* pinballMachine);
	virtual ~SelfTest();

	void onNotifySubject(EventType event, byte value);

	void IncrementTestValue();
	void DecrementTestValue();

	bool EventUpDownButton(bool upButton);
	void StartTest(byte event);
	void DoTest();
	void DoTestLed();
	void DoTestCoin();
	void DoTestOutput();
	void DoTestInput();
	void EventToInput(byte valueToSend);
	void DisplayInput(byte valueToSend);
	void DoPlaySound(bool board);
	void DoSfxOnOff();

	void FinishTest();
	void loop();

protected:
	byte m_MenuTest;
	int m_startTestValue;
	NewTimer *m_timerAuto;
	PinballMachine* m_Pinball;

	char m_szOut[15];
	char m_szHexa[15];


};

#endif
