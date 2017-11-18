/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Port.h"

//-------------------------------------------------------//
Port::Port(Pinball *pinball, const char *szName, int portNumber):PinballObject(szName,pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Port Constructor");
	#endif

	m_portNumber = portNumber;
    m_enabled = true;
}

//-------------------------------------------------------//
Port::~Port()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Port Destructor");
	#endif
}
