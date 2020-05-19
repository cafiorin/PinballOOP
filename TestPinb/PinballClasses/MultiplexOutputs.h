#ifndef _MULTIPLEX_OUTPUTS_H_
#define _MULTIPLEX_OUTPUTS__H_

#ifdef ARDUINOLIB
#include "Arduino.h"
#endif

#include "defines.h"

class MultiplexOutputs
{
public:
	MultiplexOutputs(const byte SIGOUTPUT2, const byte Sout10, const byte Sout11, const byte Sout12, const byte Sout13);

	void		writeChannel(byte ch, byte value, unsigned long time = TIME_COIL_ON);
	void		resetAllOutput();

private:
	int		_S1adrsPin[4];
	byte 	_sigOutput2;

	void 		_addressingS1(byte ch);
};
#endif
