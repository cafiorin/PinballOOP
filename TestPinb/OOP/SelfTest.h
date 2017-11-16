#ifndef SelfTest__INCLUDED_
#define SelfTest__INCLUDED_

#include "defines.h"
#include "pinballobject.h"

class PinballMaster;

class SelfTest : public PinballObject
{
public:
	SelfTest(PinballMaster *pinball);
	virtual ~SelfTest();

	virtual bool Init() {return true;}
	virtual void Loop() {};

	bool EventUpDownButton(PinballObject *sender, bool upButton);
	void StartTest(int event);
	void LoopTest();

protected:
	PinballMaster *m_Pinball;

	int m_MenuTest;
	int m_startTestValue;

};

#endif
