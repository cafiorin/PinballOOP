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
	void Setup(SFEMP3Shield *MP3player, HardwareSerial *serial, bool master);
#endif

#ifdef DOS
	Pinball(const char *szName, HardwareSerial *serial, bool master = false);
#endif
	virtual ~Pinball();
	char *getName() { return m_szName; }
	bool IsMaster() { return m_master; }
	void LogMessage(const char *szMessage);
	void AddPinballObject(PinballObject *Pinballobj);
	void RemovePinballObject(PinballObject *Pinballobj);
	bool Init();
	bool Loop(int value);
	void playSong(char song[], bool priority=true);
	void ChangeVolume(bool plus, uint8_t delta = 5);
	void clearDisplay(int line);
	void printText(char *text1, char *text2, char font);
	
	void sendMessageToAnotherArduino(char msg);
	char receiveMessageFromAnotherArduino(int howMany);

	Input *GetInput(int channel) { return m_Inputs[channel]; }
	Output *GetOutput(int channel) { return m_Outputs[channel]; }

	void AddPinballInput(Input *input);
	void AddPinballOutput(Output *output);

protected:
#ifdef ARDUINOLIB
	SFEMP3Shield *m_MP3player;
#endif // ARDUINOLIB

	char m_szName[10];
	bool m_master;
	HardwareSerial *m_serial;
	Vector<PinballObject *> m_PinballObjs;
	Input *m_Inputs[48];
	Output *m_Outputs[32];
};

#endif
