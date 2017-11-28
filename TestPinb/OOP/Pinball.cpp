/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "Pinball.h"
#include "PinballObject.h"
#include "HardwareSerial.h"
#include "Vector.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

#ifdef ARDUINOLIB
#include <Wire.h>
#include <SFEMP3Shield.h>

//---------------------------------------------------------------------//
Pinball::Pinball() : PinballObject("Pinball", this)
//---------------------------------------------------------------------//
{
	m_Status = StatusPinball::initializing;
	m_serial = NULL;
	m_enableSfx = true;
}


#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
Pinball::Pinball(const char *szName, HardwareSerial *serial) 
/*---------------------------------------------------------------------*/
{
	m_serial = serial;
	m_Status = StatusPinball::initializing;
	m_enableSfx = true;
}
#endif

/*---------------------------------------------------------------------*/
Pinball::~Pinball()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage("Pinball Destructor");
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	m_serial->println(szMessage);
	m_serial->flush();
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::LogMessageValue(const char *szMessage, int value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	char szDebug[MAX_SIZE_DEBUG_MESSAGE];
	sprintf(szDebug, "%s-val:%d", szMessage, value);
	m_serial->println(szDebug);
    m_serial->flush();
	#endif
}


//----------------------------------------------------//
void Pinball::playSong(char song[], bool priority /*default=true*/)
//-----------------------------------------------------------------------//
{
	char szMsg[50];
	sprintf(szMsg, "Play song: %s", song);
	LogMessage(szMsg);


	#ifdef ARDUINOLIB
	if (song != NULL)
	{
		if (priority && m_MP3player->getState() == playback)
		{
			m_MP3player->stopTrack();
		}

		int8_t result = m_MP3player->playMP3(song);
		if (result != 0)
		{
			char szMsg[50];
			sprintf(szMsg, "Error code: %d when trying to play track", result);
			LogMessage(szMsg);
		}
	}
	#endif // ARDUINOLIB

}

//-----------------------------------------------------------------------//
void Pinball::ChangeVolume(bool plus, uint8_t delta /*default = 5*/)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::ChangeVolume");
	#endif

	#ifdef DOS
	LogMessage("Change Volume");
	#endif // DOS


	#ifdef ARDUINOLIB
	union twobyte mp3_vol;
	mp3_vol.word = m_MP3player->getVolume();
	uint8_t volume = mp3_vol.byte[1];
	if(plus)
		volume += delta;
	else
		volume -= delta;

	if (volume >= 254)
	{
		volume = 254;
	}
	else if (volume <= 2)
	{
		volume = 2;
	}

	m_MP3player->setVolume(volume, volume);
	#endif // ARDUINOLIB
}

//-----------------------------------------------------------------------//
void Pinball::sendMessageToAnotherArduino(int address, char msg)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::sendMessageToAnotherArduino");
	#endif

	#ifdef ARDUINOLIB
	if (m_enableSfx)
	{
		// send the data
		Wire.beginTransmission(address); // transmit to device
		Wire.write(msg);
		Wire.endTransmission();
	}
	#endif
}



//-----------------------------------------------------------------------//
char Pinball::receiveMessageFromAnotherArduino(int howMany)
//-----------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	LogMessage("Pinball::receiveMessageFromAnotherArduino");
#endif

#ifdef ARDUINOLIB
	while (Wire.available() > 0)
	{
		char c = Wire.read(); // receive byte as a character
		DataReceived(c);
	}
#endif // ARDUINOLIB
	return 0;
}



