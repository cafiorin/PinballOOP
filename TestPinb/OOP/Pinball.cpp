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
Pinball::Pinball()
//---------------------------------------------------------------------//
{
	m_Status = StatusPinball::initializing;
	m_serial = NULL;
	m_MP3player = NULL;
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
	LogMessageOut(F("Pinball Destructor"));
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	if (m_serial != NULL)
	{
		m_serial->println(szMessage);
		m_serial->flush();
		delay(100);
	}
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::LogMessageOut(const __FlashStringHelper *szMessage)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	if (m_serial != NULL)
	{
		m_serial->println(szMessage);
		m_serial->flush();
		delay(100);
	}
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::LogMessageValue(const char *szMessage, uint8_t value)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	if (m_serial != NULL)
	{
		char szDebug[MAX_SIZE_DEBUG_MESSAGE];
		if (strlen(szMessage) + 15 < MAX_SIZE_DEBUG_MESSAGE)
		{
			sprintf(szDebug, "%s - value:%d", szMessage, value);
			m_serial->println(szDebug);
			m_serial->flush();
			delay(100);
		}
}
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::LogMessageValueOut(const __FlashStringHelper *szMessage, uint8_t value)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	if (m_serial != NULL)
	{
		m_serial->print(szMessage);
		m_serial->print(F(":"));
		m_serial->print(value);
		m_serial->println("");
		m_serial->flush();
		delay(100);
    }
	#endif
}

//----------------------------------------------------//
void Pinball::playSong(char song[], bool priority /*default=true*/)
//-----------------------------------------------------------------------//
{
	char szMsg[50];
	if (strlen(szMsg) < 50)
	{
		sprintf(szMsg, "Play song: %s", song);
		LogMessage(szMsg);
	}


	#ifdef ARDUINOLIB
	if (song != NULL && m_MP3player != NULL)
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
	LogMessageOut(F("Pinball::ChangeVolume"));
	#endif

	#ifdef DOS
	LogMessage("Change Volume");
	#endif // DOS


#ifdef ARDUINOLIB
	if (m_MP3player != NULL)
	{
		union twobyte mp3_vol;
		mp3_vol.word = m_MP3player->getVolume();
		uint8_t volume = mp3_vol.byte[1];
		if (plus)
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
	}
	#endif // ARDUINOLIB
}

//-----------------------------------------------------------------------//
void Pinball::sendMessageToAnotherArduino(uint8_t address, char msg)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessageOut(F("Pinball::sendMessageToAnotherArduino"));
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
char Pinball::receiveMessageFromAnotherArduino(uint8_t howMany)
//-----------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	LogMessageOut(F("Pinball::receiveMessageFromAnotherArduino"));
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



