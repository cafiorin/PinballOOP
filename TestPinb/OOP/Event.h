/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Event__INCLUDED_)
#define Event__INCLUDED_

#include "defines.h"
#include "PinballObject.h"
#include "SequencerLeds.h"

class Event
{
public:
	Event(int idEvent) { m_IdEvent = idEvent; }
	virtual ~Event() {};
	int GetIdEvent() { return m_IdEvent; }

private:
	int m_IdEvent;
};


#endif // !defined(Event__INCLUDED_)
