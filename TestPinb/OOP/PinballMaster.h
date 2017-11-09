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
#endif

#ifdef DOS
	PinballMaster(const char *szName, HardwareSerial *serial);
#endif

	virtual ~PinballMaster();
	Menu *m_Menu;
	Multiplex *m_Multiplex;

	virtual bool NotifyEvent(int id, int event);
	virtual bool Init();

	#ifdef ARDUINOLIB
	PinballMaster *m_PinballMaster;
	#endif

};

#endif
