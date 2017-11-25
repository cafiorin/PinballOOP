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
#include "DefinesMp3.h"

#ifdef DOS
#include "PinballMaster.h"
#endif // DOS


#ifdef ARDUINOLIB
#include <Wire.h>
PinballSlave *m_PinballSlave = NULL;

//-----------------------------------------------------------------------//
void receiveMessageFromAnotherArduinoSlave(int howMany)
//-----------------------------------------------------------------------//
{
	m_PinballSlave->receiveMessageFromAnotherArduino(howMany);
}

//-----------------------------------------------------------------------//
void SetupWire()
//-----------------------------------------------------------------------//
{
	Wire.begin(ADDRESS_SLAVE); // join I2C bus using this address
	Wire.onReceive(receiveMessageFromAnotherArduinoSlave); // register event to handle requests
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

/*---------------------------------------------------------------------*/
void PinballSlave::Setup(SFEMP3Shield *MP3player, HardwareSerial *serial)
/*---------------------------------------------------------------------*/
{
	m_serial = serial;
	m_MP3player = MP3player;
	playSong(MP3_STARTBUTTONPORT);
	Init();
}

#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballSlave::PinballSlave(const char *szName, HardwareSerial *serial) : Pinball(szName, serial)
/*---------------------------------------------------------------------*/
{
	m_PinballMaster = NULL;
	m_Status = StatusPinball::initializing;
<<<<<<< HEAD

	#ifdef DEBUGMESSAGES
=======
	
	#ifdef DEBUGMESSAGESCREATION
>>>>>>> 100661e6dee3b3d54eb7cb80f222eb79a8c56a8b
	LogMessage("PinballSlave Constructor");
	#endif
}
#endif

/*---------------------------------------------------------------------*/
PinballSlave::~PinballSlave()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage("PinballSlave Destructor");
	#endif
}

/*---------------------------------------------------------------------*/
bool PinballSlave::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave Init");
	#endif

	m_Status = StatusPinball::waitingmessages;
	return true;
}


/*---------------------------------------------------------------------*/
bool PinballSlave::Loop(int value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("PinballSlave::Loop");
	#endif

	return true;
}


/*---------------------------------------------------------------------*/
void PinballSlave::DataReceived(char c)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballSlave::DataReceived");
	#endif

	switch (c)
	{
		case INIT_THEME:
		{
			playSong(MP3_THEME); //TODO:
		}
		break;
	}
}
