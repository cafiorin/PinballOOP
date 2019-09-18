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
	Output(uint8_t portNumber);
	virtual ~Output();

	bool IsTurnOn(){return m_turnOn;}
	void TurnOn();
	void TurnOnByTimer(unsigned long time = TIME_COIL_ON);
	void TurnOnByDelay(unsigned long time = TIME_COIL_ON);
	void TurnOff();
	virtual bool Init();
	virtual bool NotifyEvent(Object *sender, uint8_t event, uint8_t value);

protected:
	bool m_turnOn;

private:
	Timer *m_TimerOn;
};
#endif // !defined(EA_A5DC726B_BD74_4c6c_8409_19F521E789F5__INCLUDED_)
