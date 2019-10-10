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

class Timer;

class Input : public Port
{

public:
	Input(uint8_t portNumber, PinballObject *parent=NULL);
	virtual ~Input();

	bool GetInput();
	void SetDebounceRead(uint8_t debounce){m_debounceRead = debounce;}
	bool SetInput(bool value);

private:
	uint8_t m_debounceRead;    // the debounce time; increase if the output flickers
	uint8_t m_inputWithSameValueCount;
	uint8_t m_QuantDebouncePerSecond;
	uint8_t m_NumberTriesDebounce;
	bool m_InputValue;
	bool m_Edge;
	Timer* m_timer;
	PinballObject *m_parent;

	void CheckDebounce();

protected:
	bool NotifyEvent(Object* /*sender*/, uint8_t event, uint8_t /*value*/);
};
#endif // !defined(_Input__INCLUDED_)
