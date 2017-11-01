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


#ifdef ARDUINO
#include <Wire.h>
const int address_master = 4;  // the address to be used by the communicating devices
PinballSlave *m_PinballSlave = NULL;

//-----------------------------------------------------------------------//
void receiveMessageFromAnotherArduino(int howMany)
//-----------------------------------------------------------------------//
{
	while (Wire.available() > 0)
	{
		char c = Wire.read(); // receive byte as a character

		char msg[6];
		sprintf(msg, "%d", c);
		char sw[] = "SW";
		m_PinballSlave->printText(sw, msg, 1);
	}
}

//-----------------------------------------------------------------------//
void SetupWire()
//-----------------------------------------------------------------------//
{
	Wire.begin(address_master); // join I2C bus using this address
	Wire.onReceive(receiveMessageFromAnotherArduino); // register event to handle requests
}

//-----------------------------------------------------------------------//
void sendMessageToAnotherArduino(char c)
//-----------------------------------------------------------------------//
{
	// send the data
	Wire.beginTransmission(5); // transmit to device
	Wire.write(c);
	Wire.endTransmission();
}

#endif // ARDUINO
/*---------------------------------------------------------------------*/


//							C L A S S


/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
#ifdef ARDUINO
PinballSlave::PinballSlave(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial, bool master = false) : Pinball(szName, serial, true)
#endif

#ifdef DOS
PinballSlave::PinballSlave(const char *szName, HardwareSerial *serial) : Pinball(szName, serial, true)
#endif
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave Constructor");
#endif

#ifdef ARDUINO
	m_PinballSlave = this;
	SetupWire();
#endif

	m_PinballMaster = NULL;
}

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
