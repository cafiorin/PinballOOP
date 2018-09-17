/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Pinball.h"
#include "Object.h"
#include "PinballObject.h"
#include "HardwareSerial.h"
#include "Vector.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

#ifdef ARDUINOLIB
#include <Wire.h>
#include <SFEMP3Shield.h>

SFEMP3Shield *Pinball::m_MP3player = NULL;
#endif


/*---------------------------------------------------------------------*/
Pinball::Pinball() : Object()
/*---------------------------------------------------------------------*/
{
	m_Multiplex = NULL;
	m_Status = StatusPinball::initializing;
	m_enableSfx = true;
}

/*---------------------------------------------------------------------*/
Pinball::~Pinball()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Pinball Destructor"));
	#endif
}

//----------------------------------------------------//
void Pinball::playSong(char song[], bool priority /*default=true*/)
//-----------------------------------------------------------------------//
{
	char szMsg[30]; //12 + 10 + 1
	sprintf(szMsg, "Play song:%s", song);
	LogMessage(szMsg);

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
	LogMessage(F("Pinball::ChangeVolume"));
	#endif

	#ifdef DOS
	LogMessage(F("Change Volume"));
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
	LogMessage(F("Pinball::sendMessageToAnotherArduino"));
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
	LogMessage(F("Pinball::receiveMessageFromAnotherArduino"));
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


/*---------------------------------------------------------------------*/
void Pinball::AddPinballInput(Input *input)
/*---------------------------------------------------------------------*/
{
	if (input != NULL)
	{
		#ifdef DEBUGMESSAGESCREATION
		LogMessage(F(":AddPinballInput"));
		#endif

		uint8_t port = input->GetPortNumber();
		if (port >= 0 && port < MAX_INPUTCHANNELS)
			m_Inputs[port] = input;
	}
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballOutput(Output *output)
/*---------------------------------------------------------------------*/
{
	if (output != NULL)
	{
		#ifdef DEBUGMESSAGESCREATION
		LogMessage(F(":AddPinballOutput"));
		#endif

		uint8_t port = output->GetPortNumber();
		if (port >= 0 && port < MAX_OUTPUTCHANNELS)
			m_Outputs[port] = output;
	}
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Pinball::AddPinballObject"));
	#endif

	m_PinballObjs.push_back(Pinballobj);
}

/*---------------------------------------------------------------------*/
void Pinball::RemovePinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage(F("Pinball::RemovePinballObject"));
#endif

	m_PinballObjs.pop_back(Pinballobj);
}

