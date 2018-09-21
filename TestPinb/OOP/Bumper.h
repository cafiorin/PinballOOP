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
	Bumper(uint8_t portNumberInput, uint8_t portNumberOutput, uint8_t Led);
	virtual ~Bumper();
	virtual bool NotifyEvent(Object *sender, uint8_t event, uint8_t value);

protected:
	Input *m_input;
	Output *m_output;
	uint8_t m_Led;
	Timer *m_TimerLed;

};
#endif // !defined(SlingShot__INCLUDED_)
