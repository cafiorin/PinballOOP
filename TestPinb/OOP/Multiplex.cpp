/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Utils.h"
#include "PinballMaster.h"
#include "Input.h"
#include "Output.h"
#include "PinballObject.h"
#include "Multiplex.h"
#include "HardwareSerial.h"

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

#ifdef DOS
#include "HardwareSerial.h"
#endif // DOS

static const uint8_t _muxChAddress[16][4] = 
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
Multiplex::Multiplex(const uint8_t S0,const uint8_t S1,const uint8_t S2,const uint8_t S3,
	const uint8_t SIGINPUT1, const uint8_t SIGINPUT2, const uint8_t SIGINPUT3, 
	const uint8_t latchPin, const uint8_t clockPin, const uint8_t dataPin,
	const uint8_t SIGOUTPUT2, const uint8_t Sout10, const uint8_t Sout11, const uint8_t Sout12, const uint8_t Sout13) : PinballObject()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Multiplex Constructor"));
	#endif

	_adrsPin[0] = S0;
	_adrsPin[1] = S1;
	_adrsPin[2] = S2;
	_adrsPin[3] = S3;

	_S1adrsPin[0] = Sout10;
	_S1adrsPin[1] = Sout11;
	_S1adrsPin[2] = Sout12;
	_S1adrsPin[3] = Sout13;

	_sigInput1 = SIGINPUT1;
	_sigInput2 = SIGINPUT2;
	_sigInput3 = SIGINPUT3;

	_sigOutput2 = SIGOUTPUT2;

	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;


	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		pinMode(_adrsPin[i], OUTPUT);
		digitalWrite(_adrsPin[i], LOW);

		pinMode(_S1adrsPin[i], OUTPUT);
		digitalWrite(_S1adrsPin[i], LOW);
	}

	pinMode(_sigInput1, INPUT);
	pinMode(_sigInput2, INPUT);
	pinMode(_sigInput3, INPUT);

	pinMode(_sigOutput2, OUTPUT);

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

	resetAllOutput();
}

//-----------------------------------------------
void Multiplex::resetAllOutput()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::resetAllOutput"));
	#endif

	digitalWrite(_sigOutput2, LOW);

	for (uint8_t i = 0; i < 16; i++)
	{
		_addressingS1(i);
		delay(25);
	}
}


//-----------------------------------------------
void Multiplex::writeChannel(uint8_t ch, uint8_t value)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::writeChannel"));
	#endif

	if (ch < 16)
	{
		writeChannelLatch(ch, value);
	}
	else if (ch < 32)
	{
		digitalWrite(_sigOutput2, value);
		delay(100);
		_addressingS1(ch - 16);
		delay(100);
	}
}

//-----------------------------------------------
void Multiplex::writeChannelLatch(uint8_t ch, uint8_t value)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::writeChannelLatch"));
	#endif

	if (ch < 16)
	{
		bool out1[8];
		bool out2[8];
		for(uint8_t i=0; i < 8; i++)
		{
			Output* pOutput1 = m_Pinball->GetOutput(i);
			if (pOutput1 != NULL)
			{
				out1[i] = pOutput1->IsTurnOn();
			}
			else
			{
				out1[i] = false;
			}


			Output* pOutput2 = m_Pinball->GetOutput(i+8);
			if (pOutput2 != NULL)
			{
				out2[i] = pOutput2->IsTurnOn();
			}
			else
			{
				out2[i] = false;
			}
		}
		byte LSB = ToByte(out1);
		byte MSB = ToByte(out2);
		
		#ifdef DEBUGMESSAGES
		const char szNumber[20];
		sprintf(szNumber, "%x e %x", LSB, MSB);
		LogMessageToConstChar(szNumber);
		#endif

		digitalWrite(_latchPin, 0);
		shiftOut(MSB);
		shiftOut(LSB);
		digitalWrite(_latchPin, 1);
	}
}

//-----------------------------------------------
void Multiplex::shiftOut(byte myDataOut)
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


//-----------------------------------------------
uint8_t Multiplex::readChannel(uint8_t ch)
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
			return digitalRead(_sigInput1);
		}
		else if (ch >= 16 && ch < 32)
		{
			_addressing(ch-16);
			return digitalRead(_sigInput2);
		}
		else if (ch > 32)
		{
			_addressing(ch-32);
			return digitalRead(_sigInput2);
		}
	}

	return 0;
}

//-----------------------------------------------
void Multiplex::Loop()
//-----------------------------------------------
{
	if (IsEnabled())
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("Multiplex::Loop"));
		#endif

		uint8_t read = 0;
		Input *input = NULL;

		for (uint8_t ch = 0; ch < 16; ch++)
		{
			_addressing(ch);

			//channel 0-15
			read = digitalRead(_sigInput1);
			input = m_Pinball->GetInput(ch);
			if (input != NULL)
			{
				input->SetInput(read);
			}

			//channel 16-31
			read = digitalRead(_sigInput2);
			input = m_Pinball->GetInput(ch+16);
			if (input != NULL)
			{
				input->SetInput(read);
			}

			//channel 32-47
			read = digitalRead(_sigInput3);
			input = m_Pinball->GetInput(ch+32);
			if (input != NULL)
			{
				input->SetInput(read);
			}
		}

		#ifdef DEBUGINPUTS
		if (m_Serial != NULL)
		{
			m_Serial->println(F("Portas ... "));

			for (uint8_t ch = 0; ch < 48; ch++)
			{
				Input *input = m_Pinball->GetInput(ch);
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
}


//-----------------------------------------------
void Multiplex::_addressing(uint8_t ch)
//-----------------------------------------------
{
	if (ch < 16)
	{
		uint8_t i;
		for (i = 0; i < 4; i++)
		{
			digitalWrite(_adrsPin[i], _muxChAddress[ch][i]);
		}
	}
}

//-----------------------------------------------
void Multiplex::_addressingS1(uint8_t ch)
//-----------------------------------------------
{
	if (ch < 16)
	{
		uint8_t i;
		for (i = 0; i < 4; i++)
		{
			digitalWrite(_S1adrsPin[i], _muxChAddress[ch][i]);
		}
	}
}