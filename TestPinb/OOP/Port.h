/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(EA_6839F9BC_FCE5_403e_AC3C_D7C5DF31399B__INCLUDED_)
#define EA_6839F9BC_FCE5_403e_AC3C_D7C5DF31399B__INCLUDED_

#include "defines.h"
#include "PinballObject.h"

class Port : public PinballObject
{

public:
	Port(Pinball *pinball, const char *szName, int portNumber);
	virtual ~Port();
	void Enable(){m_enabled=true;}
	void Disable(){m_enabled=false;}

protected:
	int m_portNumber;
	bool m_enabled;

};
#endif // !defined(EA_6839F9BC_FCE5_403e_AC3C_D7C5DF31399B__INCLUDED_)
