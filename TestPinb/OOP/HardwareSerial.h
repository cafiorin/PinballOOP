/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "defines.h"

class HardwareSerial
{
public:
	HardwareSerial();
	~HardwareSerial();
	void println(const char *szLog);
};

#endif
