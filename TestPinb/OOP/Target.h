/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Target__INCLUDED_)
#define Target__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "PinballObject.h"

class Timer;
class Input;

class Target : public PinballObject
{
public:
	Target(const char *szName, PinballMaster *pinball, uint8_t portNumberInput, uint8_t led);
	virtual ~Target();
	virtual bool Init(StatusPinball status);
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);

	bool IsHit() { return m_hit; }

protected:
	Input *m_input;
	uint8_t m_led;
	bool m_hit;
	Timer *m_timerBlinkLed;

};
#endif // !defined(Target__INCLUDED_)
