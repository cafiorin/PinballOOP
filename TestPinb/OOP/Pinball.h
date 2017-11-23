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

class Pinball : public PinballObject
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

	void AddPinballObject(PinballObject *Pinballobj);
	void RemovePinballObject(PinballObject *Pinballobj);
	void playSong(char song[], bool priority=true);
	void ChangeVolume(bool plus, uint8_t delta = 5);

	void sendMessageToAnotherArduino(int address, char msg);
	char receiveMessageFromAnotherArduino(int howMany);
	virtual void DataReceived(char c) {};

	Input *GetInput(int channel) { return m_Inputs[channel]; }
	Output *GetOutput(int channel) { return m_Outputs[channel]; }

	void AddPinballInput(Input *input);
	void AddPinballOutput(Output *output);

	void EnableSFX(bool enable) { m_enableSfx = enable; }
	bool IsEnabledSFX() { return m_enableSfx; }
	bool m_enableSfx;

protected:
#ifdef ARDUINOLIB
	SFEMP3Shield *m_MP3player;
#endif // ARDUINOLIB

	HardwareSerial *m_serial;
	Vector<PinballObject *> m_PinballObjs;
	Input *m_Inputs[MAX_INPUTCHANNELS];
	Output *m_Outputs[MAX_OUTPUTCHANNELS];

	StatusPinball m_Status;
	AttractMode *m_AttractMode;
};

#endif
