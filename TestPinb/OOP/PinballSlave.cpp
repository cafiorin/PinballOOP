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
void receiveMessageFromAnotherArduinoSlave(uint8_t howMany)
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
}

#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballSlave::PinballSlave(const char *szName, HardwareSerial *serial) : Pinball(szName, serial)
/*---------------------------------------------------------------------*/
{
	m_PinballMaster = NULL;
	m_Status = StatusPinball::initializing;
	
	#ifdef DEBUGMESSAGESCREATION
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
bool PinballSlave::Loop(uint8_t value)
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
		case COMM_TEST_SOUND:
		{
			playSong(MP3_THEME_STAGE0);
		}
		break;

		case COMM_INIT_THEME:
		{
			playSong(MP3_THEME);
		}
		break;

		case COMM_INIT_THEME_STAGE0:
		{
			playSong(MP3_THEME_STAGE0);
		}
		break;

		case COMM_INIT_THEME_STAGE1:
		{
			playSong(MP3_THEME_STAGE1);
		}
		break;

		case COMM_INIT_THEME_STAGE2:
		{
			playSong(MP3_THEME_STAGE2);
		}
		break;

		case COMM_INIT_THEME_STAGE3:
		{
			playSong(MP3_THEME_STAGE3);
		}
		break;
		
		case COMM_INIT_THEME_STAGE4:
		{
			playSong(MP3_THEME_STAGE4);
		}
		break;
		
		case COMM_INIT_THEME_STAGE5:
		{
			playSong(MP3_THEME_STAGE5);
		}
		break;
	}
}
