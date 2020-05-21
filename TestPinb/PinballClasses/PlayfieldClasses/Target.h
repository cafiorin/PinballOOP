/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Target__INCLUDED_)
#define Target__INCLUDED_

#include "..\\Observer.h"
#include "..\\ChangeableStatus.h"


class Timer;
class BitInput;
class LedControl;
class Input;
class NewTimer;
class Subject;

class Target : public Observer, public ChangeableStatus
{
public:
	Target(BitInput* input, LedControl* ledControl, byte led);

	//virtual
	virtual ~Target();
	void changeStatus(StatusPinballMachine status);
	void onNotifySubject(EventType event, byte value);

	void AddObserverToSlingShotActivated(Observer* observer);
	bool IsHit() { return m_hit; }

protected:
	byte m_led;
	bool m_hit;
	NewTimer *m_timerBlinkLed;
	LedControl* m_LedControl;
	Subject* m_EventToHitTarget;
	StatusPinballMachine m_status;
};
#endif // !defined(Target__INCLUDED_)
