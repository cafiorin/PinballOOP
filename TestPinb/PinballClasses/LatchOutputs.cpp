
#include "..\OOP\Utils.h"
#include "..\OOP\defines.h"
#include "LatchOutputs.h"
#include "BitOutput.h"

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

//-----------------------------------------------
LatchOutputs::LatchOutputs(const byte latchPin, const byte clockPin, const byte dataPin)
//-----------------------------------------------
{
#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("LatchOutputs Constructor"));
#endif

	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

	resetAllOutput();

	for (byte i = 0; i < MAX_OUTPUTS; i++)
	{
		outputs[i] = new BitOutput(this, i);
	}
}

//-----------------------------------------------
void LatchOutputs::resetAllOutput()
//-----------------------------------------------
{
#ifdef DEBUGMESSAGES
	LogMessage(F("LatchOutputs::resetAllOutput"));
#endif
}

//-----------------------------------------------
void LatchOutputs::writeChannelLatch(byte ch, byte /*value*/)
//-----------------------------------------------
{
#ifdef DEBUGMESSAGES
	LogMessage(F("LatchOutputs::writeChannelLatch"));
#endif

	bool out1[8];
	bool out2[8];
	bool out3[8];
	bool out4[8];

	for (byte i = 0; i < 8; i++)
	{
		out1[i] = outputs[i]->IsTurnOn();
		out2[i] = outputs[i + 8]->IsTurnOn();
		out3[i] = outputs[i + 16]->IsTurnOn();
		out4[i] = outputs[i + 24]->IsTurnOn();
	}
	byte LSB1 = ToByte(out1);
	byte LSB2 = ToByte(out2);
	byte MSB1 = ToByte(out3);
	byte MSB2 = ToByte(out4);

	#ifdef DEBUGMESSAGES
	char szNumber[20];
	sprintf(szNumber, "%x %x %x %x", LSB1, LSB2, MSB1, MSB2);
	LogMessageToConstChar(szNumber);
	#endif

	digitalWrite(_latchPin, 0);
	shiftOut(MSB2);
	shiftOut(MSB1);
	shiftOut(LSB2);
	shiftOut(LSB1);
	digitalWrite(_latchPin, 1);
}

//-----------------------------------------------
void LatchOutputs::shiftOut(byte myDataOut)
//-----------------------------------------------
{
	int i = 0;
	int pinState;

	digitalWrite(_dataPin, 0);
	digitalWrite(_clockPin, 0);

	for (i = 7; i >= 0; i--)
	{
		digitalWrite(_clockPin, 0);

		if (myDataOut & (1 << i))
		{
			pinState = 1;
		}
		else
		{
			pinState = 0;
		}

		//Sets the pin to HIGH or LOW depending on pinState
		digitalWrite(_dataPin, pinState);
		//register shifts bits on upstroke of clock pin  
		digitalWrite(_clockPin, 1);
		//zero the data pin after shift to prevent bleed through
		digitalWrite(_dataPin, 0);
	}

	//stop shifting
	digitalWrite(_clockPin, 0);
}

