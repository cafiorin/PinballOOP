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

class Output : public Port
{
public:
	Output(const char *szName, Pinball *pinball, int portNumber);
	virtual ~Output();

	int GetPortNumber() { return m_portNumber; }
	bool IsTurnOn(){return m_turnOn;}
	void TurnOn();
	void TurnOnByTimer(long time=TIME_COIL_ON);
	void TurnOff();
	virtual bool Init();
	virtual bool Loop(int value);

protected:
	bool m_turnOn;
	long m_timerDelay;
	int m_portNumber;

private:	
	Timer *m_TimerOn;
};
#endif // !defined(EA_A5DC726B_BD74_4c6c_8409_19F521E789F5__INCLUDED_)
