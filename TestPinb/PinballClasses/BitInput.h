/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _BitInput__INCLUDED_
#define _BitInput__INCLUDED_

#include "..\\OOP\defines.h"
#include "Runnable.h"

class Subject;
class Observer;

class BitInput : public Runnable
{

public:
	BitInput(byte portNumber);

	bool GetInput();
	void SetInput(bool value) { m_inputValue = value; }
	void loop();
	void AddObserverToEdgePositive(Observer* observer);

private:
	bool m_inputValue;
	byte m_portNumber;
	unsigned long buttonDownMs;

	Subject* m_EventEdgePositive;
};
#endif 

