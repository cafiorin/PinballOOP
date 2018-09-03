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
	HardwareSerial(uint8_t xlog=1,uint8_t ylog=1);
	~HardwareSerial();
	void println(const char *szLog);
	void jumpline();
	void flush(){};
	void ResetLine() { m_line = 0; }
	void printone(const char *szLog);
	void printbox(uint8_t width, uint8_t height, char *szTitle);
	void print(const char *szLog);
	void print(char *szLog);
	void print(int value);

	uint8_t m_line;
	char m_strings[MAX_STRINGS][50];
	uint8_t m_XInit;
	uint8_t m_YInit;

};
#endif


#endif
