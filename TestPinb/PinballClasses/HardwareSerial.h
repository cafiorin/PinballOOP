/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef HardwareSerial__INCLUDED_
#define HardwareSerial__INCLUDED_

#include "defines.h"

#ifdef DOS


#include "defines.h"
#include "Vector.h"

#define MAX_STRINGS 25
class HardwareSerial
{
public:
	HardwareSerial(byte xlog=1,byte ylog=1);
	~HardwareSerial();
	void println(const char *szLog);
	void jumpline();
	void flush(){};
	void ResetLine() { m_line = 0; }
	void printone(const char *szLog);
	void printbox(byte width, byte height, char *szTitle);
	void print(const char *szLog);
	void print(char *szLog);
	void print(int value);
	void println(byte value);

	int m_line;
	char m_strings[MAX_STRINGS][50];
	int m_XInit;
	int m_YInit;

};
#endif


#endif
