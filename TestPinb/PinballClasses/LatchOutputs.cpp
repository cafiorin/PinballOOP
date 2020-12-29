
#include "Utils.h"
#include "defines.h"
#include "LatchOutputs.h"
#include "BitOutput.h"
#include "Logger.h"

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

//-----------------------------------------------
LatchOutputs::LatchOutputs(const byte latchPin, const byte clockPin, const byte dataPin, byte resetPin)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("LatchOutputs Constructor"));
	#endif

	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	
	pinMode(resetPin, OUTPUT);
	
	digitalWrite(resetPin, 0);
	delay(100);
	digitalWrite(resetPin, 1);

	for (byte i = 0; i < MAX_OUTPUTS; i++)
	{
		outputs[i] = new BitOutput(this, i);
	}

	writeAllOutput();
	resetAllOutput();
}

//-----------------------------------------------
LatchOutputs::~LatchOutputs()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("LatchOutputs Destructor"));
	#endif
	for (byte i = 0; i < MAX_OUTPUTS; i++)
	{
		delete outputs[i];
	}
}


//-----------------------------------------------
void LatchOutputs::resetAllOutput()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("LatchOutputs::resetAllOutput"));
	#endif

	for (byte i = 0; i < MAX_OUTPUTS; i++)
	{
		outputs[i]->TurnOff();
	}
}

//-----------------------------------------------
void LatchOutputs::writeAllOutput()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("LatchOutputs::writeAllOutput"));
	#endif

	bool outLsb[8];
	bool outMsb[8];

	for (byte i = 0; i < 8; i++)
	{
		outLsb[i] = outputs[i]->IsTurnOn();
		outMsb[i] = outputs[i + 8]->IsTurnOn();
	}
	byte LSB = ToByte(outLsb);
	byte MSB = ToByte(outMsb);

	#ifdef DEBUGMESSAGES
	char szNumber[20];
	sprintf(szNumber, "%x %x", LSB, MSB);
	Logger::LogMessageToConstChar(szNumber);
	#endif

	digitalWrite(_latchPin, 0);
	shiftOut(MSB);
	shiftOut(LSB);
	digitalWrite(_latchPin, 1);
}

//-----------------------------------------------
BitOutput* LatchOutputs::GetOuput(byte ch)
//-----------------------------------------------
{
	if (ch < MAX_OUTPUTS)
	{
		return outputs[ch];
	}
	return NULL;
}

//-----------------------------------------------
void LatchOutputs::AddOutputObserverToTurnOn(byte ch, Observer* observer)
//-----------------------------------------------
{
	if (ch < MAX_OUTPUTS)
	{
		this->outputs[ch]->AddObserverToTurnOn(observer);
	}
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

