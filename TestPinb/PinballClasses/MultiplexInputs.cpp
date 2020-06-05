/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Utils.h"
#include "MultiplexInputs.h"
#include "Logger.h"

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

#define MAX_MUXINPUTS 48
#define INPUTS_BY_CHIP 16

static const byte _muxChAddress[INPUTS_BY_CHIP][4] =
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
MultiplexInputs::MultiplexInputs(const byte S0, const byte S1, const byte S2, const byte S3,
					 const byte SIGINPUT1, const byte SIGINPUT2, const byte SIGINPUT3) : Runnable()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("MultiplexInputs Constructor"));
	#endif

	_adrsPin[0] = S0;
	_adrsPin[1] = S1;
	_adrsPin[2] = S2;
	_adrsPin[3] = S3;

	_sigInput1 = SIGINPUT1;
	_sigInput2 = SIGINPUT2;
	_sigInput3 = SIGINPUT3;

	for (byte i = 0; i < 4; i++)
	{
		pinMode(_adrsPin[i], OUTPUT);
		digitalWrite(_adrsPin[i], LOW);
	}

	pinMode(_sigInput1, INPUT);
	pinMode(_sigInput2, INPUT);
	pinMode(_sigInput3, INPUT);

	for (byte i = 0; i < MAX_MUXINPUTS; i++)
	{
		inputs[i] = new BitInput(i);
	}
}

//-----------------------------------------------
MultiplexInputs::~MultiplexInputs()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("Multiplex Destructor"));
	#endif

	for (byte i = 0; i < MAX_MUXINPUTS; i++)
	{
		delete inputs[i];
	}
}


//-----------------------------------------------
byte MultiplexInputs::readChannel(byte ch)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("Multiplex::readChannel"));
	#endif

	if (ch < MAX_MUXINPUTS)
	{
		if (ch < INPUTS_BY_CHIP)
		{
			_addressing(ch);
			return (byte) digitalRead(_sigInput1);
		}
		else if (ch >= INPUTS_BY_CHIP && ch < INPUTS_BY_CHIP*2)
		{
			_addressing(ch - INPUTS_BY_CHIP);
			return (byte) digitalRead(_sigInput2);
		}
		else if (ch > INPUTS_BY_CHIP*2)
		{
			_addressing(ch - INPUTS_BY_CHIP*2);
			return (byte) digitalRead(_sigInput3);
		}
	}

	return 0;
}

//-----------------------------------------------
void MultiplexInputs::loop()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	Logger::LogMessage(F("Multiplex::Loop"));
	#endif

	byte read = 0;
	for (byte ch = 0; ch < INPUTS_BY_CHIP; ch++)
	{
		_addressing(ch);

		//channel 0-15
		read = (byte) digitalRead(_sigInput1);
		inputs[ch]->SetInput(read);

		//channel 16-31
		read = (byte) digitalRead(_sigInput2);
		inputs[ch + INPUTS_BY_CHIP]->SetInput(read);

		//channel 32-47
		read = (byte) digitalRead(_sigInput3);
		inputs[ch + INPUTS_BY_CHIP*2]->SetInput(read);
	}

	#ifdef DEBUGINPUTS
		Logger::LogMessage(F("Ports ... "));

		for (byte ch = 0; ch < 48; ch++)
		{
			BitInput* input = GetInput(ch);
			if (input != NULL)
			{
				Logger::LogMessage(F("Port "));
				Logger::LogMessageByte(ch);
				Logger::LogMessage(F("==>"));
				Logger::LogMessageByte(input->GetInput());
				Logger::LogMessage(F("<=="));
			}
		}
	#endif

}


//-----------------------------------------------
void MultiplexInputs::_addressing(byte ch)
//-----------------------------------------------
{
	if (ch < 16)
	{
		byte i;
		for (i = 0; i < 4; i++)
		{
			digitalWrite(_adrsPin[i], _muxChAddress[ch][i]);
		}
	}
}

//-----------------------------------------------
void MultiplexInputs::AddInputObserverToEdgePositive(byte ch, Observer* observer)
//-----------------------------------------------
{
	if (ch < MAX_MUXINPUTS)
	{
		this->inputs[ch]->AddObserverToEdgePositive(observer);
	}
}

//-----------------------------------------------
BitInput* MultiplexInputs::GetInput(byte ch)
//-----------------------------------------------
{
	if (ch < MAX_MUXINPUTS)
	{
		return inputs[ch];
	}
	return NULL;
}

