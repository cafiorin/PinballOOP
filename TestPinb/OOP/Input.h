/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(EA_493584A8_374D_4c41_813B_7DEB885806F1__INCLUDED_)
#define EA_493584A8_374D_4c41_813B_7DEB885806F1__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Port.h"

class Input : public Port
{

public:
	Input(const char *szName, Pinball *pinball, int portNumber);
	virtual ~Input();
	bool GetInput();
	bool CheckEdgePositive();
	void SetDebounceDelay(long debounce){m_debounceDelay = debounce;}
	virtual bool Init();
	virtual bool Loop(int value);

	#ifdef DOS
	void EmulateInput(bool value) { m_emulateInput = value; }
	#endif

private:
	bool m_lastState;
	long m_lastDebounceTime;  // the last time the output pin was toggled
	long m_debounceDelay;    // the debounce time; increase if the output flickers
	bool m_startReading;
	
	#ifdef DOS
	bool m_emulateInput;
	#endif

};
#endif // !defined(EA_493584A8_374D_4c41_813B_7DEB885806F1__INCLUDED_)
