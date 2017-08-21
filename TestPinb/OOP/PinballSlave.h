/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballSlave__INCLUDED_
#define PinballSlave__INCLUDED_

#include "defines.h"
#include "Vector.h"
#include "Pinball.h"

#ifdef ARDUINO
#include <SFEMP3Shield.h>
#include <Wire.h>
#include "ht1632pinball.h"
#endif // ARDUINO

#ifdef DOS
#include "PinballMaster.h"
#endif // DOS

class PinballObject;
class HardwareSerial;

class PinballSlave : public Pinball
{
public:
#ifdef ARDUINO
	PinballSlave(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif
#ifdef DOS
	PinballSlave(const char *szName, HardwareSerial *serial);

	PinballMaster *m_PinballMaster;
	void SetPinballMaster(PinballMaster *pinball) { m_PinballMaster = pinball; }

#endif
	virtual ~PinballSlave();
	virtual void Loop(int value);

};

#endif
