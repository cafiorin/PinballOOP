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
}


#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
Pinball::Pinball(const char *szName, HardwareSerial *serial) : PinballObject (szName, this)
/*---------------------------------------------------------------------*/
{
	m_serial = serial;
	m_Status = StatusPinball::initializing;
}
#endif

/*---------------------------------------------------------------------*/
Pinball::~Pinball()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Destructor");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		delete m_PinballObjs[i];
	}

}

/*---------------------------------------------------------------------*/
void Pinball::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	m_serial->println(szMessage);
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballInput(Input *input)
/*---------------------------------------------------------------------*/
{
	if (input != NULL)
	{
		m_Inputs[input->GetPortNumber()] = input;
	}
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballOutput(Output *output)
/*---------------------------------------------------------------------*/
{
	if (output != NULL)
	{
		m_Outputs[output->GetPortNumber()] = output;
	}
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::AddPinballObject");
	#endif

	m_PinballObjs.push_back(Pinballobj);
}

/*---------------------------------------------------------------------*/
void Pinball::RemovePinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage("Pinball::RemovePinballObject");
#endif

	m_PinballObjs.pop_back(Pinballobj);
}

//-----------------------------------------------------------------------//
void Pinball::playSong(char song[], bool priority /*default=true*/)
//-----------------------------------------------------------------------//
{
	#ifdef DOS
	char szMsg[50];
	sprintf(szMsg, "Play song: %s", song);
	LogMessage(szMsg);
	#endif // DOS


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
	// send the data
	Wire.beginTransmission(address); // transmit to device
	Wire.write(msg);
	Wire.endTransmission();
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



