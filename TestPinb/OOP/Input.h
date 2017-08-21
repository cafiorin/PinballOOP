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
	Input(const char *szName, Pinball *pinball, int portNumber);
	virtual ~Input();
	bool GetInput();
	bool CheckEdgePositive();
	void SetDebounceDelay(long debounce){m_debounceDelay = debounce;}
	int GetPortNumber() { return m_portNumber; }

	virtual bool Init();
	virtual bool Loop(int value);

	#ifdef DOS
	void EmulateInput(bool value) { m_emulateInput = value; }
	#endif

private:
	bool m_lastState;
	long m_debounceDelay;    // the debounce time; increase if the output flickers
	bool m_startReading;
	Timer *m_TimerDebounce;
	int m_portNumber;

	#ifdef DOS
	bool m_emulateInput;
	#endif

};
#endif // !defined(_Input__INCLUDED_)
