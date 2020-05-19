/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BitOutput__INCLUDED_
#define BitOutput__INCLUDED_

#include "defines.h"

#include "Initializable.h"
#include "Observer.h"
#include "LatchOutputs.h"
#include "NewTimer.h"

class BitOutput : public Initializable, public Observer
{
public:
	BitOutput(LatchOutputs* latch, byte portNumber);

	bool IsTurnOn(){return m_turnOn;}
	void TurnOn();
	void TurnOnByTimer(unsigned long time = TIME_COIL_ON);
	void TurnOnByDelay(unsigned long time = TIME_COIL_ON);
	void Pulse(unsigned long time = TIME_COIL_ON);
	void TurnOff();
	byte GetPortNumber() { return m_portNumber; }

	//virtual
	virtual ~BitOutput();
	void init();
	void AddObserverToTurnOn(Observer* observer);

protected:
	bool m_turnOn;
	byte m_portNumber;
	Subject* m_EventToTurnOn;
	LatchOutputs *m_LatchOutputs;

private:
	NewTimer *m_TimerOn;
	void onNotifySubject(EventType event, byte value);
};

#endif 

