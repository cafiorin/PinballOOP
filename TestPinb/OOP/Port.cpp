/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Port.h"

//-------------------------------------------------------//
Port::Port(uint8_t portNumber):PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Port Constructor"));
	#endif

	m_portNumber = portNumber;
    m_Enabled = true;
}

//-------------------------------------------------------//
Port::~Port()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Port Destructor"));
	#endif
}
