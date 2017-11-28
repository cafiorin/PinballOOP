/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Bumper__INCLUDED_)
#define Bumper__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "PinballObject.h"

class Timer;
class Input;
class Output;

class Bumper : public PinballObject
{
public:
	Bumper(const char *szName, PinballMaster *pinball, int portNumberInput, int portNumberOutput, int Led);
	virtual ~Bumper();
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

protected:
	Input *m_input;
	Output *m_output;
	int m_Led;
	Timer *m_TimerLed;

};
#endif // !defined(SlingShot__INCLUDED_)
