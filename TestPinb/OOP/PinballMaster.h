/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballMaster__INCLUDED_
#define PinballMaster__INCLUDED_

#ifdef ARDUINOLIB
#include <SFEMP3Shield.h>
#include <Wire.h>
#endif // ARDUINOLIB

#include "defines.h"
#include "Vector.h"
#include "Pinball.h"

class PinballObject;
class HardwareSerial;
class Menu;
class Multiplex;

class PinballMaster : public Pinball
{
public:
#ifdef ARDUINOLIB
	PinballMaster();
	void Setup(SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif

#ifdef DOS
	PinballMaster(const char *szName, HardwareSerial *serial);
#endif

	virtual ~PinballMaster();
	Menu *m_Menu;
	Multiplex *m_Multiplex;

	void clearDisplay(int line);
	void printText(char *text1, char *text2, char font);

	virtual bool NotifyEvent(int id, int event);
	virtual bool Init();
	virtual bool Loop(int value);
	virtual void DataReceived(char c);

	#ifdef ARDUINOLIB
	PinballMaster *m_PinballMaster;
	#endif

};

#endif
