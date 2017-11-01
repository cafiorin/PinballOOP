/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(_Input__INCLUDED_)
#define _Input__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Port.h"
#include "Timer.h"

class Input : public Port
{

public:
	Input(const char *szName, Pinball *pinball, int portNumber, PinballObject *pinballObject);
	virtual ~Input();

	bool GetInput();
	void SetDebounceDelay(long debounce){m_debounceDelay = debounce;}
	int GetPortNumber() { return m_portNumber; }

	virtual bool Init();
	virtual bool Loop(int value);

	void SetInput(bool value);

private:
	long m_debounceDelay;    // the debounce time; increase if the output flickers
	Timer *m_TimerDebounce;
	int m_portNumber;
	bool m_InputValue;
	PinballObject *m_pinballObjectParent;

};
#endif // !defined(_Input__INCLUDED_)
