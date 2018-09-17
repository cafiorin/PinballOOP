/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(ReturnKickBall__INCLUDED_)
#define ReturnKickBall__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "PinballObject.h"

class Input;
class Output;
class Timer;

class ReturnKickBall : public PinballObject
{
public:
	ReturnKickBall(uint8_t portNumberInput, uint8_t portNumberOutput,uint8_t led);
	virtual ~ReturnKickBall();
	virtual bool Init();
	virtual bool NotifyEvent(Object *sender, Event *event);
	void SetReturnBall(bool returnBallOn);

protected:
	Input *m_input1;
	Output *m_output;
	uint8_t m_led;
	bool m_returnBallOn;
	Timer *m_timerBlinkLed;

};
#endif // !defined(ReturnKickBall__INCLUDED_)
