/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(KickoutHole__INCLUDED_)
#define KickoutHole__INCLUDED_

#include "Observer.h"
#include "Initializable.h"
#include "BitInput.h"

class BitOutput;
class Subject;

class KickoutHole : public Observer, public Initializable
{
public:
	KickoutHole(BitInput* Input, BitOutput* portNumberOutput);

	//virtual
	virtual ~KickoutHole();
	void init();
	void onNotifySubject(EventType event, byte value);

	void LanchBall();
	bool IsThereBall() { m_input->GetInput(); }
	void AddObserverToBallKickHole(Observer* observer);

protected:
	BitInput* m_input;
	BitOutput* m_output;
	Subject* m_EventToBallKickHole;

};
#endif // !defined(KickoutHole__INCLUDED_)
