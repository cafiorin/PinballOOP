#include "MultiplexOutputs.h"
#include "Utils.h"
#include "Logger.h"

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

static const byte _muxChAddress[16][4] =
{
	{0,0,0,0}, //channel 0
	{1,0,0,0}, //channel 1
	{0,1,0,0}, //channel 2
	{1,1,0,0}, //channel 3
	{0,0,1,0}, //channel 4
	{1,0,1,0}, //channel 5
	{0,1,1,0}, //channel 6
	{1,1,1,0}, //channel 7
	{0,0,0,1}, //channel 8
	{1,0,0,1}, //channel 9
	{0,1,0,1}, //channel 10
	{1,1,0,1}, //channel 11
	{0,0,1,1}, //channel 12
	{1,0,1,1}, //channel 13
	{0,1,1,1}, //channel 14
	{1,1,1,1}  //channel 15
};

//-----------------------------------------------
MultiplexOutputs::MultiplexOutputs(const byte SIGOUTPUT2, const byte Sout10, const byte Sout11, const byte Sout12, const byte Sout13)
//-----------------------------------------------
{
#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("MultiplexOutputs Constructor"));
#endif

	_sigOutput2 = SIGOUTPUT2;
	pinMode(_sigOutput2, OUTPUT);
	digitalWrite(_sigOutput2, LOW);

	_S1adrsPin[0] = Sout10;
	_S1adrsPin[1] = Sout11;
	_S1adrsPin[2] = Sout12;
	_S1adrsPin[3] = Sout13;

	byte i;
	for (i = 0; i < 4; i++)
	{
		pinMode(_S1adrsPin[i], OUTPUT);
		digitalWrite(_S1adrsPin[i], LOW);
	}

	resetAllOutput();
}

//-----------------------------------------------
void MultiplexOutputs::resetAllOutput()
//-----------------------------------------------
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("MultiplexOutputs::resetAllOutput"));
#endif

	digitalWrite(_sigOutput2, LOW);

	for (byte i = 0; i < 16; i++)
	{
		_addressingS1(i);
		delay(25);
	}
}


//-----------------------------------------------
void MultiplexOutputs::writeChannel(byte ch, byte value, unsigned long time /*= TIME_COIL_ON*/)
//-----------------------------------------------
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("MultiplexOutputs::writeChannel"));
#endif

	if (ch >= 16 && ch < 32)
	{
		digitalWrite(_sigOutput2, LOW);
		delay(10);
		_addressingS1(ch - 16);
		delay(10);

		if (value == HIGH)
		{
			//pulse
			digitalWrite(_sigOutput2, HIGH);
			delay(time);
			digitalWrite(_sigOutput2, LOW);
			delay(10);
		}
	}
}


//-----------------------------------------------
void MultiplexOutputs::_addressingS1(byte ch)
//-----------------------------------------------
{
	if (ch < 16)
	{
		byte i;
		for (i = 0; i < 4; i++)
		{
			digitalWrite(_S1adrsPin[i], _muxChAddress[ch][i]);
		}
	}
}