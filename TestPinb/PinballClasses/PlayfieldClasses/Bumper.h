/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Bumper__INCLUDED_)
#define Bumper__INCLUDED_

#include "..\\Observer.h"

class Timer;
class BitInput;
class BitOutput;
class Subject;

class Bumper : public Observer
{
public:
	Bumper(BitInput *input, BitOutput* output, BitOutput* ledOutput);
	virtual ~Bumper();
	void onNotifySubject(EventType event, byte value);
	void AddObserverToBumperActivated(Observer* observer);

protected:
	BitInput *m_input;
	BitOutput *m_output;
	BitOutput *m_Led;
	Subject* m_EventToBumperActivated;
};
#endif // !defined(SlingShot__INCLUDED_)
