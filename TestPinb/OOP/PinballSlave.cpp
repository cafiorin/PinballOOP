/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PinballSlave.h"
#include "PinballObject.h"
#include "Pinball.h"
#include "HardwareSerial.h"
#include "Vector.h"
#include "Utils.h"
#include "Input.h"

#ifdef DOS
#include "PinballMaster.h"
#endif // DOS


#ifdef ARDUINOLIB
#include <Wire.h>
const int address_master = 4;  // the address to be used by the communicating devices
PinballSlave *m_PinballSlave = NULL;

//-----------------------------------------------------------------------//
void receiveMessageFromAnotherArduino(int howMany)
//-----------------------------------------------------------------------//
{
	m_PinballSlave->receiveMessageFromAnotherArduino(howMany);
}

//-----------------------------------------------------------------------//
void SetupWire()
//-----------------------------------------------------------------------//
{
	Wire.begin(address_master); // join I2C bus using this address
	Wire.onReceive(receiveMessageFromAnotherArduino); // register event to handle requests
}

#endif // ARDUINOLIB


/*---------------------------------------------------------------------*/
//							C L A S S
/*---------------------------------------------------------------------*/

#ifdef ARDUINOLIB
/*---------------------------------------------------------------------*/
PinballSlave::PinballSlave()
/*---------------------------------------------------------------------*/
{
	m_PinballSlave = this;
	SetupWire();
}
#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballSlave::PinballSlave(const char *szName, HardwareSerial *serial) : Pinball(szName, serial, true)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave Constructor");
	#endif

	m_PinballMaster = NULL;
}
#endif

/*---------------------------------------------------------------------*/
PinballSlave::~PinballSlave()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave Destructor");
	#endif
}

/*---------------------------------------------------------------------*/
bool PinballSlave::Loop(int value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("Pinball::Loop");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		if (m_PinballObjs[i]->Loop(value))
		{
			#ifdef DEBUGMESSAGES
			char szMsg[50];
			sprintf(szMsg, "%s Loop return true", m_PinballObjs[i]->getName());
			LogMessage(szMsg);
			#endif
		}
	}

	return true;
}
