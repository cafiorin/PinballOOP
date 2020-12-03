/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _BitInput__INCLUDED_
#define _BitInput__INCLUDED_

#include "defines.h"
#include "Runnable.h"

class Subject;
class Observer;

class BitInput : public Runnable
{

public:
	BitInput(byte portNumber);
	virtual ~BitInput();

	bool GetInput();
	void SetInput(bool value) 
	{ 
		m_inputValueOld = m_inputValue;
		m_inputValue = value;
	}
	void loop();
	void AddObserverToEdgePositive(Observer* observer);
	byte GetPortNumber() { return m_portNumber; }
private:
	bool m_inputValue;
	bool m_inputValueOld;
	byte m_portNumber;
	unsigned long buttonDownMs;

	Subject* m_EventEdgePositive;
};
#endif 

