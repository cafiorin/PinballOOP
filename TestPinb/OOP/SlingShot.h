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
	SlingShot(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberInput2, int portNumberOutput, Multiplex *multiplex);
	virtual ~SlingShot();
	virtual bool Init();
	virtual bool Loop(int value);
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

protected:
	Input *m_input1;
	Input *m_input2;
	Output *m_output;

};
#endif // !defined(SlingShot__INCLUDED_)
