/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(_InputControl__INCLUDED_)
#define _InputControl__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "PinballObject.h"
#include "Multiplex.h"

class InputControl : public PinballObject
{

public:
	InputControl(const char *szName, Pinball *pinball, Multiplex *multiplex);
	virtual ~InputControl();
	virtual bool Init();
	virtual bool Loop(int value);

protected:
	Multiplex *m_multiplex;

private:

};
#endif // !defined(_InputControl__INCLUDED_)
