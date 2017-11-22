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

class Input : public Port
{

public:
	Input(const char *szName, Pinball *pinball, int portNumber, PinballObject *pinballObject);
	virtual ~Input();

	bool GetInput();
	void SetDebounceRead(int debounce){m_debounceRead = debounce;}

	virtual bool Init();

	bool SetInput(bool value);

private:
	int m_debounceRead;    // the debounce time; increase if the output flickers
	int m_debounceCount;
	bool m_InputValue;
	bool m_Edge;
	PinballObject *m_pinballObjectParent;

	void CheckDebounce();
};
#endif // !defined(_Input__INCLUDED_)
