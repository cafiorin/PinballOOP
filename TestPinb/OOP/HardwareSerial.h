/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef HardwareSerial__INCLUDED_
#define HardwareSerial__INCLUDED_

#include "defines.h"

class HardwareSerial
{
public:
	HardwareSerial();
	~HardwareSerial();
	void println(const char *szLog);
};

#endif
