/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballSlave__INCLUDED_
#define PinballSlave__INCLUDED_

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

class PinballSlave : public Pinball
{
public:
#ifdef ARDUINO
	PinballSlave(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial);
#endif
#ifdef DOS
	PinballSlave(const char *szName, HardwareSerial *serial);
#endif
	virtual ~PinballSlave();
};

#endif
