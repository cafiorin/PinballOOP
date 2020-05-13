
#ifndef _LATCH_OUTPUTS_H_
#define _LATCH_OUTPUTS_H_

#include "..\\OOP\\defines.h"
class BitOutput;
class Observer;

#define MAX_OUTPUTS 16

class LatchOutputs 
{
public:
	LatchOutputs(const byte latchPin, const byte clockPin, const byte dataPin);
	~LatchOutputs();

	void AddOutputObserverToTurnOn(byte ch, Observer* observer);
	void writeAllOutput();
	void resetAllOutput();
	BitOutput* GetOuput(byte ch);

private:
	byte _latchPin;
	byte _clockPin;
	byte _dataPin;
	
	BitOutput* outputs[MAX_OUTPUTS];

	void shiftOut(byte myDataOut);
};
#endif

