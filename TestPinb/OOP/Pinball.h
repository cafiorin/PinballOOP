/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Pinball__INCLUDED_
#define Pinball__INCLUDED_

#ifdef ARDUINO
#include <SFEMP3Shield.h>
#include <Wire.h>
#include "ht1632pinball.h"
#endif // ARDUINO

#include "defines.h"
#include "Vector.h"

class PinballObject;
class HardwareSerial;

class Pinball
{
public:
#ifdef ARDUINO
	Pinball(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial, bool master=false);
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
	void Init();
	void Loop(int value);
	void playSong(char song[], bool priority=true);
	void ChangeVolume(bool plus, uint8_t delta = 5);
	void clearDisplay(int line);
	void printText(char *text1, char *text2, char font);
	void sendMessageToAnotherArduino(char msg);
	char receiveMessageFromAnotherArduino();

protected:
#ifdef ARDUINO
	SFEMP3Shield *m_MP3player;
#endif // ARDUINO

	char m_szName[10];
	bool m_master;
	HardwareSerial *m_serial;
	Vector<PinballObject *> m_PinballObjs;
};

#endif
