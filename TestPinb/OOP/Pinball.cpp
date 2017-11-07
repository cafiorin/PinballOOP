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

/*---------------------------------------------------------------------*/
#ifdef ARDUINO
#include <Wire.h>

Pinball::Pinball(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial, bool master = false)
#endif

#ifdef DOS
Pinball::Pinball(const char *szName, HardwareSerial *serial, bool master) : PinballObject (szName, this)
#endif
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_master = master;
	m_serial = serial;
	
	for (int ch = 0; ch < MAX_INPUTCHANNELS; ch++)
	{
		m_Inputs[ch] = NULL;
	}

	for (int ch = 0; ch < MAX_OUTPUTCHANNELS; ch++)
	{
		m_Outputs[ch] = NULL;
	}


	#ifdef ARDUINO
	m_MP3player = MP3player;
	#endif

	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Constructor");
	#endif
}

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


/*---------------------------------------------------------------------*/
bool Pinball::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::Init");
	#endif

	printText("Pinball", "init", 0);

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Init();
	}

	printText("Pinball", "OK", 0);
	return true;
}


/*---------------------------------------------------------------------*/
bool Pinball::Loop(int value)
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

//-----------------------------------------------------------------------//
void Pinball::playSong(char song[], bool priority /*default=true*/)
//-----------------------------------------------------------------------//
{
	#ifdef DOS
	char szMsg[50];
	sprintf(szMsg, "Play song: %s", song);
	LogMessage(szMsg);
	#endif // DOS


	#ifdef ARDUINO
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
	#endif // ARDUINO

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


	#ifdef ARDUINO
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
	#endif // ARDUINO
}

//-----------------------------------------------------------------------//
void Pinball::clearDisplay(int line)
//-----------------------------------------------------------------------//
{
	if (!m_master)
		return;

	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::clearDisplay");
	#endif


	#ifdef ARDUINO
	char textcol[] = "        ";

	if (line == 0) // Clear All
	{
		textcolor1(0, 1, textcol, RED, 1);
		textcolor1(0, 9, textcol, GREEN, 1);
	}
	else if (line == 1)
	{
		textcolor1(0, 1, textcol, RED, 1);
	}
	else
	{
		textcolor1(0, 9, textcol, GREEN, 1);
	}
	#endif
}

//-----------------------------------------------------------------------//
void Pinball::printText(char *text1, char *text2, char font)
//-----------------------------------------------------------------------//
{
	if (!m_master)
		return;

	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::printText");
	#endif


	#ifdef DOS
	int xCursor, yCursor;
	getCursorXY(xCursor, yCursor);

	int x = 70;
	int y = 1;
	clrbox(x, y, x+10, y+3, BLACK);
	box(x, y, x+10, y+3, y+6, y+6, "Display");

	setcolor(RED);
	gotoxy(x+2, y+1);
	printf(text1);

	setcolor(GREEN);
	gotoxy(x+2, y+2);
	printf(text2);

	gotoxy(xCursor, yCursor);
	#endif


	#ifdef ARDUINO
	clearDisplay(0);
	textcolor1(1, 1, text1, RED, font);
	textcolor1(1, 8 + font, text2, GREEN, font);
	#endif
}

//-----------------------------------------------------------------------//
void Pinball::sendMessageToAnotherArduino(char msg)
//-----------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	LogMessage("Pinball::sendMessageToAnotherArduino");
#endif

}

//-----------------------------------------------------------------------//
char Pinball::receiveMessageFromAnotherArduino()
//-----------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	LogMessage("Pinball::receiveMessageFromAnotherArduino");
#endif

#ifdef ARDUINO
	while (Wire.available() > 0)
	{
		char c = Wire.read(); // receive byte as a character

		char msg[6];
		sprintf(msg, "%d", c);
		char sw[] = "SW";
		m_thisSR1->printText(sw, msg, 1);
		m_thisSR1->AcionaChave(c);
	}
#endif // ARDUINO
	return 0;
}



