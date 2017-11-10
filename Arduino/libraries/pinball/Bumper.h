/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Bumper__INCLUDED_)
#define Bumper__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

class Bumper : public PinballObject
{
public:
	Bumper(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput,Multiplex *multiplex);
	virtual ~Bumper();
	virtual bool Init();
	virtual bool Loop(int value);
	virtual bool NotifyEvent(int id, int event);

protected:
	Input *m_input;
	Output *m_output;

};
#endif // !defined(SlingShot__INCLUDED_)
