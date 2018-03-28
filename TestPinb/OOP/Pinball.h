/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Pinball__INCLUDED_
#define Pinball__INCLUDED_

#include "defines.h"

#ifdef ARDUINOLIB
#include <SFEMP3Shield.h>
#include <Wire.h>
#endif // ARDUINOLIB

#include "Vector.h"
#include "PinballObject.h"
#include "AttractMode.h"

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
	void LogMessageValue(const char *szMessage, uint8_t value);

	void playSong(char song[], bool priority=true);
	void ChangeVolume(bool plus, uint8_t delta = 5);

	void sendMessageToAnotherArduino(uint8_t address, char msg);
	char receiveMessageFromAnotherArduino(uint8_t howMany);
	virtual void DataReceived(char c) {};

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
