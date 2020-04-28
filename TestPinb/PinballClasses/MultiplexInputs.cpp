/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\\OOP\\Utils.h"
#include "MultiplexInputs.h"

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
MultiplexInputs::MultiplexInputs(const byte S0, const byte S1, const byte S2, const byte S3,
					 const byte SIGINPUT1, const byte SIGINPUT2, const byte SIGINPUT3) : Runnable()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Multiplex Constructor"));
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

	for (byte i = 0; i < 48; i++)
	{
		inputs[i] = new BitInput(i);
	}
}

//-----------------------------------------------
byte MultiplexInputs::readChannel(byte ch)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::readChannel"));
	#endif

	if (ch >= 0 && ch < 48)
	{
		if (ch < 16)
		{
			_addressing(ch);
			return (byte) digitalRead(_sigInput1);
		}
		else if (ch >= 16 && ch < 32)
		{
			_addressing(ch - 16);
			return (byte) digitalRead(_sigInput2);
		}
		else if (ch > 32)
		{
			_addressing(ch - 32);
			return (byte) digitalRead(_sigInput2);
		}
	}

	return 0;
}

//-----------------------------------------------
void MultiplexInputs::loop()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("Multiplex::Loop"));
	#endif

	byte read = 0;
	for (byte ch = 0; ch < 16; ch++)
	{
		_addressing(ch);

		//channel 0-15
		read = (byte) digitalRead(_sigInput1);
		inputs[ch]->SetInput(read);

		//channel 16-31
		read = (byte) digitalRead(_sigInput2);
		inputs[ch + 16]->SetInput(read);

		//channel 32-47
		read = (byte) digitalRead(_sigInput3);
		inputs[ch + 32]->SetInput(read);
	}

	#ifdef DEBUGINPUTS
	if (m_Serial != NULL)
	{
		m_Serial->println(F("Portas ... "));

		for (byte ch = 0; ch < 48; ch++)
		{
			Input* input = m_Pinball->GetInput(ch);
			if (input != NULL)
			{
				m_Serial->print(F("Porta "));
				m_Serial->print(ch);
				m_Serial->print(F("==>"));
				m_Serial->print((int)input->GetInput());
				m_Serial->println(F("<=="));
			}
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

