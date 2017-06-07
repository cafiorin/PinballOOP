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
