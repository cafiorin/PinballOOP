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

/*---------------------------------------------------------------------*/
PinballSlave::PinballSlave()
/*---------------------------------------------------------------------*/
{
}

/*---------------------------------------------------------------------*/
void PinballSlave::Setup(SFEMP3Shield *MP3player, HardwareSerial *serial)
/*---------------------------------------------------------------------*/
{
	m_Serial = serial;
	m_Pinball = this;
	m_MP3player = MP3player;
	m_Status = StatusPinball::waitingmessages;

	m_Multiplex = NULL;
	m_LedControl = NULL;
	m_enableSfx = false;
}

#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballSlave::PinballSlave(HardwareSerial *serial) : Pinball()
/*---------------------------------------------------------------------*/
{
	m_Status = StatusPinball::initializing;
	m_Serial = serial;
	m_Pinball = this;

	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballSlave Constructor"));
	#endif
}
#endif

/*---------------------------------------------------------------------*/
PinballSlave::~PinballSlave()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballSlave Destructor"));
	#endif
}

/*---------------------------------------------------------------------*/
bool PinballSlave::Loop(uint8_t /*value*/)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("PinballSlave::Loop"));
	#endif

	return true;
}


/*---------------------------------------------------------------------*/
void PinballSlave::DataReceived(char c)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballSlave::DataReceived"));
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
