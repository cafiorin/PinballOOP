/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(ReturnKickBall__INCLUDED_)
#define ReturnKickBall__INCLUDED_

#include "..\\Observer.h"
#include "..\\ChangeableStatus.h"

class BitInput;
class BitOutput;
class NewTimer;
class Subject;
class LedControl;

class ReturnKickBall : public Observer, ChangeableStatus
{
public:
	ReturnKickBall(BitInput* input, BitOutput* output, LedControl* ledControl, byte led);
	void SetReturnBall(bool returnBallOn);

	//virtual
	virtual ~ReturnKickBall();
	void onNotifySubject(EventType event, byte value);
	void changeStatus(StatusPinballMachine status);

protected:
	BitInput *m_input1;
	BitOutput *m_output;
	byte m_led;
	bool m_returnBallOn;
	NewTimer *m_timerBlinkLed;
	LedControl* m_LedControl;
	StatusPinballMachine m_status;
};
#endif // !defined(ReturnKickBall__INCLUDED_)
