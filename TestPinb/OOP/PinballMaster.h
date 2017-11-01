/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballMaster__INCLUDED_
#define PinballMaster__INCLUDED_

#ifdef ARDUINO
#include <SFEMP3Shield.h>
#include <Wire.h>
#include "ht1632pinball.h"
#endif // ARDUINO

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
#ifdef ARDUINO
	PinballMaster(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif
#ifdef DOS
	PinballMaster(const char *szName, HardwareSerial *serial);
#endif
	virtual ~PinballMaster();
	Menu *m_Menu;
	Multiplex *m_Multiplex;

	virtual void sendMessageToAnotherArduino(char msg);
	virtual char receiveMessageFromAnotherArduino();
	virtual bool NotifyEvent(int id, int event);

};

#endif
