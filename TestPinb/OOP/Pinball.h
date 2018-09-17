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
class Object;
class Multiplex;

class Pinball : public Object
{
public:
	Pinball();
	virtual ~Pinball();

	StatusPinball GetStatus(){return m_Status;}

	void AddPinballObject(PinballObject *Pinballobj);
	void RemovePinballObject(PinballObject *Pinballobj);
	void AddPinballInput(Input *input);
	void AddPinballOutput(Output *output);

	Input *GetInput(uint8_t channel)
	{
		if (channel < MAX_INPUTCHANNELS) return m_Inputs[channel];
		return NULL;
	}

	Output *GetOutput(uint8_t channel)
	{
		if (channel < MAX_OUTPUTCHANNELS) return m_Outputs[channel];
		return NULL;
	}

	Multiplex *GetMultiplex() { return m_Multiplex; }

	void playSong(char song[], bool priority=true);
	void ChangeVolume(bool plus, uint8_t delta = 5);

	void sendMessageToAnotherArduino(uint8_t address, char msg);
	char receiveMessageFromAnotherArduino(uint8_t howMany);
	virtual void DataReceived(char ) {};

	void EnableSFX(bool enable) { m_enableSfx = enable; }
	bool IsEnabledSFX() { return m_enableSfx; }
	bool m_enableSfx;

	bool IsPlaying() { return m_Status == StatusPinball::playingmode; }

	//virtual
	virtual void PlaySongToInput(uint8_t ) {}
	virtual void clearDisplay(uint8_t =0 ) {}
	virtual void printText(char *, char *, char ) {}

protected:
	#ifdef ARDUINOLIB
	static SFEMP3Shield *m_MP3player;
	#endif // ARDUINOLIB
	StatusPinball m_Status;
	Vector<PinballObject *> m_PinballObjs;
	Input *m_Inputs[MAX_INPUTCHANNELS];
	Output *m_Outputs[MAX_OUTPUTCHANNELS];

	Multiplex *m_Multiplex;
};

#endif
