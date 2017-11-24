/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(ReturnKickBall__INCLUDED_)
#define ReturnKickBall__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

class ReturnKickBall : public PinballObject
{
public:
	ReturnKickBall(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput, Multiplex *multiplex);
	virtual ~ReturnKickBall();
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

protected:
	Input *m_input1;
	Output *m_output;
};
#endif // !defined(ReturnKickBall__INCLUDED_)
