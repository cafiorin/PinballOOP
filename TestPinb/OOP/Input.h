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
	Input(uint8_t portNumber, PinballObject *pinballObjectParent=NULL);
	virtual ~Input();

	bool GetInput();
	void SetDebounceRead(uint8_t debounce){m_debounceRead = debounce;}
	bool SetInput(bool value);

private:
	uint8_t m_debounceRead;    // the debounce time; increase if the output flickers
	uint8_t m_debounceCount;
	bool m_InputValue;
	bool m_Edge;
	PinballObject *m_pinballObjectParent;

	void CheckDebounce();
};
#endif // !defined(_Input__INCLUDED_)
