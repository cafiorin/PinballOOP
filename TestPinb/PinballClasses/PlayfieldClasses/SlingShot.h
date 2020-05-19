/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(SlingShot__INCLUDED_)
#define SlingShot__INCLUDED_

#include "..\\Observer.h"
#include "..\\BitInput.h"

class BitOutput;
class Subject;

class SlingShot : public Observer
{
public:
	SlingShot(BitInput* input1, BitInput* input2, BitOutput* output);

	//virtual
	virtual ~SlingShot();
	void onNotifySubject(EventType event, byte value);
	void AddObserverToSlingShotActivated(Observer* observer);

protected:
	BitInput* m_input1;
	BitInput* m_input2;
	BitOutput* m_output;

	Subject* m_EventToSlingShotActivated;

};
#endif // !defined(SlingShot__INCLUDED_)
