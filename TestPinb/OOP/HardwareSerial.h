/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef HardwareSerial__INCLUDED_
#define HardwareSerial__INCLUDED_

#include "defines.h"
#include "Vector.h"

#define MAX_STRINGS 25
class HardwareSerial
{
public:
	HardwareSerial(int xlog=1);
	~HardwareSerial();
	void println(const char *szLog);
	
	int m_line;
	char m_strings[MAX_STRINGS][50];
	int m_XInit;

};

#endif
