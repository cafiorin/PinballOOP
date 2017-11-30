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
	ReturnKickBall(const char *szName, PinballMaster *pinball, int portNumberInput, int portNumberOutput,int led);
	virtual ~ReturnKickBall();
	virtual bool Init(StatusPinball status);
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);
	void SetReturnBall(bool returnBallOn);

protected:
	Input *m_input1;
	Output *m_output;
	int m_led;
	bool m_returnBallOn;
	Timer *m_timerBlinkLed;

};
#endif // !defined(ReturnKickBall__INCLUDED_)
