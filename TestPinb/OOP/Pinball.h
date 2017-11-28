/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Pinball__INCLUDED_
#define Pinball__INCLUDED_

#ifdef ARDUINOLIB
#include <SFEMP3Shield.h>
#include <Wire.h>
#endif // ARDUINOLIB

#include "defines.h"
#include "Vector.h"
#include "PinballObject.h"
#include "AttractMode.h"

enum StatusPinball
{
	initializing,
	menusetup,
	menutest,
	attractmode,
	getplayers,
	playingmode,
	waitingmessages
};


#define MAX_INPUTCHANNELS 48
#define MAX_OUTPUTCHANNELS 32

class HardwareSerial;
class Input;
class Output;
class SFEMP3Shield;

class Pinball 
{
public:
#ifdef ARDUINOLIB
	Pinball();
#endif

#ifdef DOS
	Pinball(const char *szName, HardwareSerial *serial);
#endif
	virtual ~Pinball();
	void LogMessage(const char *szMessage);
	void LogMessageValue(const char *szMessage, int value);

	void playSong(char song[], bool priority=true);
	void ChangeVolume(bool plus, uint8_t delta = 5);

	void sendMessageToAnotherArduino(int address, char msg);
	char receiveMessageFromAnotherArduino(int howMany);
	virtual void DataReceived(char c) {};
	virtual void PlaySongToInput(int portNumber) {}

	void EnableSFX(bool enable) { m_enableSfx = enable; }
	bool IsEnabledSFX() { return m_enableSfx; }
	bool m_enableSfx;

protected:
#ifdef ARDUINOLIB
	SFEMP3Shield *m_MP3player;
#endif // ARDUINOLIB

	HardwareSerial *m_serial;

	StatusPinball m_Status;
	AttractMode *m_AttractMode;
};

#endif
