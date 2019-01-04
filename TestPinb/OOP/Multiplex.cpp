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
Multiplex::Multiplex(const uint8_t S0,const uint8_t S1,const uint8_t S2,const uint8_t S3,const uint8_t SIG, const uint8_t OUTSIG, const uint8_t SIG1, const uint8_t SIG2, const uint8_t chipSelect1, const uint8_t chipSelect2, const uint8_t chipSelect3, const uint8_t chipSelect4, const uint8_t chipSelect5) : PinballObject()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Multiplex Constructor"));
	#endif

	_adrsPin[0] = S0;
	_adrsPin[1] = S1;
	_adrsPin[2] = S2;
	_adrsPin[3] = S3;

	_sig = SIG;
	_sig1= SIG1;
	_sig2= SIG2;
	_outsig = OUTSIG;

	_chipSelect1 = chipSelect1;
	_chipSelect2 = chipSelect2;
	_chipSelect3 = chipSelect3;
	_chipSelect4 = chipSelect4;
	_chipSelect5 = chipSelect5;
}

//-----------------------------------------------
void Multiplex::setup()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::setup"));
	#endif

	uint8_t i;

	pinMode(_sig, INPUT);
	pinMode(_sig1, INPUT);
	pinMode(_sig2, INPUT);
	pinMode(_outsig, OUTPUT);

	pinMode(_chipSelect1, OUTPUT);
	digitalWrite(_chipSelect1, HIGH);

	pinMode(_chipSelect2, OUTPUT);
	digitalWrite(_chipSelect2, HIGH);

	pinMode(_chipSelect3, OUTPUT);
	digitalWrite(_chipSelect3, HIGH);

	pinMode(_chipSelect4, OUTPUT);
	digitalWrite(_chipSelect4, HIGH);

	pinMode(_chipSelect5, OUTPUT);
	digitalWrite(_chipSelect5, HIGH);

	for (i = 0; i < 4; i++)
	{
		pinMode(_adrsPin[i], OUTPUT);
		digitalWrite(_adrsPin[i],LOW);
	}

}

//-----------------------------------------------
void Multiplex::enableChip(uint8_t chipNumber)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::enableChip"));
	#endif

	// set all to Disable (HIGH)
	digitalWrite(_chipSelect1, HIGH);
	digitalWrite(_chipSelect2, HIGH);
	digitalWrite(_chipSelect3, HIGH);
	digitalWrite(_chipSelect4, HIGH);
	digitalWrite(_chipSelect5, HIGH);

	//Enable only one
	digitalWrite(chipNumber, LOW);
}

//-----------------------------------------------
void Multiplex::resetAllOutput()
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::resetAllOutput"));
	#endif

	digitalWrite(_outsig, LOW);

	digitalWrite(_chipSelect4, LOW);
	digitalWrite(_chipSelect5, LOW);

	for (uint8_t i = 0; i < 16; i++)
	{
		_addressing(i);
	}

	digitalWrite(_chipSelect4, HIGH);
	digitalWrite(_chipSelect5, HIGH);
}


//-----------------------------------------------
void Multiplex::writeChannel(uint8_t ch,uint8_t value)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::writeChannel"));
	#endif

	if (ch < 0 || ch > 32)
		return ;

	digitalWrite(_outsig, value);

	if (ch < 16)
	{
		_addressing(ch);
		enableChip(_chipSelect4);
	}
	else
	{
		ch -= 16;
		_addressing(ch);
		enableChip(_chipSelect5);
	}
}


//-----------------------------------------------
uint8_t Multiplex::readChannel(uint8_t ch)
//-----------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Multiplex::readChannel"));
	#endif

	if (ch < 0 || ch > 47)
		return 0;

	if (ch < 16)
	{
		enableChip(_chipSelect1);
		_addressing(ch);
		return digitalRead(_sig);
	}
	else if (ch >= 16 && ch < 32)
	{
		enableChip(_chipSelect2);
		_addressing(ch-16);
		return digitalRead(_sig1);
	}

	enableChip(_chipSelect3);
	_addressing(ch-32);
	return digitalRead(_sig2);
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

		digitalWrite(_chipSelect1, HIGH);
		digitalWrite(_chipSelect2, HIGH);
		digitalWrite(_chipSelect3, HIGH);

		for (uint8_t ch = 0; ch < 16; ch++)
		{
			_addressing(ch);

			uint8_t read;
			digitalWrite(_chipSelect1, LOW);
			read = digitalRead(_sig);
			digitalWrite(_chipSelect1, HIGH);
			Input *input = m_Pinball->GetInput(ch);
			if (input != NULL)
			{
				input->SetInput(read);
			}

			digitalWrite(_chipSelect2, LOW);
			read = digitalRead(_sig1);
			digitalWrite(_chipSelect2, HIGH);
			input = m_Pinball->GetInput(ch + 16);
			if (input != NULL)
			{
				input->SetInput(read);
			}

			digitalWrite(_chipSelect3, LOW);
			read = digitalRead(_sig2);
			digitalWrite(_chipSelect3, HIGH);
			input = m_Pinball->GetInput(ch + 32);
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
	uint8_t i;
	for (i = 0; i < 4; i ++)
	{
		digitalWrite(_adrsPin[i],_muxChAddress[ch][i]);
	}
}


