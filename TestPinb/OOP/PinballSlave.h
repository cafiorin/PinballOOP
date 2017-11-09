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

#ifdef ARDUINOLIB
#include <SFEMP3Shield.h>
#include <Wire.h>
#endif // ARDUINOLIB

#ifdef DOS
#include "PinballMaster.h"
#endif // DOS

class PinballObject;
class HardwareSerial;

class PinballSlave : public Pinball
{
public:
#ifdef ARDUINOLIB
	PinballSlave();
	PinballSlave *m_PinballSlave;
	void Setup(SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif

#ifdef DOS
	PinballSlave(const char *szName, HardwareSerial *serial);

	PinballMaster *m_PinballMaster;
	void SetPinballMaster(PinballMaster *pinball) { m_PinballMaster = pinball; }
#endif

	virtual ~PinballSlave();

	virtual bool Loop(int value);
	virtual bool Init();
	virtual void DataReceived(char c);
};

#endif
