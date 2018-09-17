/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(SlingShot__INCLUDED_)
#define SlingShot__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

class SlingShot : public PinballObject
{
public:
	SlingShot(uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberOutput);
	virtual ~SlingShot();
	virtual bool Init();
	virtual bool NotifyEvent(Object *sender, Event *event);

protected:
	Input *m_input1;
	Input *m_input2;
	Output *m_output;

};
#endif // !defined(SlingShot__INCLUDED_)
