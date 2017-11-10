/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Port__INCLUDED_)
#define Port__INCLUDED_

#include "defines.h"
#include "PinballObject.h"

class Port : public PinballObject
{

public:
	Port(Pinball *pinball, const char *szName, int portNumber);
	virtual ~Port();

protected:
	int m_portNumber;

};
#endif // !defined(Port__INCLUDED_)
