/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(_InputArduino__INCLUDED_)
#define _InputArduino__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Port.h"

class InputArduino : public Port
{

public:
	InputArduino(uint8_t portNumber, PinballObject *parent=NULL);
	virtual ~InputArduino();

	bool GetInput();
	void SetDebounceRead(uint8_t debounce){m_debounceRead = debounce;}
	bool SetInput(bool value);
	virtual void Loop();

private:
	uint8_t m_debounceRead;    // the debounce time; increase if the output flickers
	uint8_t m_debounceCount;
	bool m_InputValue;
	bool m_Edge;
	PinballObject *m_parent;

	void CheckDebounce();
};
#endif // !defined(_InputArduino__INCLUDED_)
