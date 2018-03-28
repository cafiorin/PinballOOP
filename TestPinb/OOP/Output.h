/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Output__INCLUDED_)
#define Output__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Port.h"
#include "Timer.h"

class Multiplex;

class Output : public Port
{
public:
	Output(const char *szName, PinballMaster *pinball, uint8_t portNumber);
	virtual ~Output();

	bool IsTurnOn(){return m_turnOn;}
	void TurnOn();
	void TurnOnByTimer(long time=TIME_COIL_ON);
	void TurnOff();
	virtual bool Init(StatusPinball status);
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);

protected:
	bool m_turnOn;
	long m_timerDelay;
	Multiplex *m_Multiplex;

private:
	Timer *m_TimerOn;
};
#endif // !defined(EA_A5DC726B_BD74_4c6c_8409_19F521E789F5__INCLUDED_)
