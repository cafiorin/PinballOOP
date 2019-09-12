/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Light__INCLUDED_)
#define Light__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Timer.h"
#include "Output.h"

class Light : public Output
{
public:
	Light(uint8_t portNumber);
	virtual ~Light();
	virtual bool NotifyEvent(Object *sender, uint8_t event, uint8_t value);

	void StartBlink(unsigned long value=700);
	void EndBlink();

protected:
	Timer *m_timerBlinking;
};
#endif 
