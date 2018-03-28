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
	Port(PinballMaster *pinball, const char *szName, uint8_t portNumber);
	virtual ~Port();
	uint8_t GetPortNumber() { return m_portNumber; }

protected:
	uint8_t m_portNumber;

};
#endif // !defined(Port__INCLUDED_)
