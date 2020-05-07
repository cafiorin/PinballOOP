
#ifndef _LATCH_OUTPUTS_H_
#define _LATCH_OUTPUTS_H_

#include "..\\OOP\\defines.h"
class BitOutput;

#define MAX_OUTPUTS 32

class LatchOutputs 
{
public:
	LatchOutputs(const byte latchPin, const byte clockPin, const byte dataPin);
	void writeChannelLatch(byte ch, byte value);
	void resetAllOutput();

private:
	byte _latchPin;
	byte _clockPin;
	byte _dataPin;
	
	BitOutput* outputs[MAX_OUTPUTS];

	void shiftOut(byte myDataOut);
};
#endif

