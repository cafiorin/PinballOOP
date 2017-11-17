#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

#include "Utils.h"
#include "Pinball.h"
#include "Input.h"
#include "Output.h"
#include "PinballObject.h"
#include "Multiplex.h"

static const int _muxChAddress[16][4] = {
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

Multiplex::Multiplex(Pinball *pinball, const int S0,const int S1,const int S2,const int S3,const int SIG, const int OUTSIG, const int chipSelect1, const int chipSelect2, const int chipSelect3, const int chipSelect4, const int chipSelect5) : PinballObject("Mult", pinball)
{
	_adrsPin[0] = S0;
	_adrsPin[1] = S1;
	_adrsPin[2] = S2;
	_adrsPin[3] = S3;

	_sig = SIG;
	_outsig = OUTSIG;

	_chipSelect1 = chipSelect1;
	_chipSelect2 = chipSelect2;
	_chipSelect3 = chipSelect3;
	_chipSelect4 = chipSelect4;
	_chipSelect5 = chipSelect5;
}

void Multiplex::setup()
{
	int i;

	pinMode(_sig, INPUT);
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

void Multiplex::enableChip(int chipNumber)
{
	// set all to Disable (HIGH)
	digitalWrite(_chipSelect1, HIGH);
	digitalWrite(_chipSelect2, HIGH);
	digitalWrite(_chipSelect3, HIGH);
	digitalWrite(_chipSelect4, HIGH);
	digitalWrite(_chipSelect5, HIGH);

	//Enable only one
	digitalWrite(chipNumber, LOW);
}

void Multiplex::resetAllOutput()
{
	digitalWrite(_outsig, LOW);

	digitalWrite(_chipSelect4, LOW);
	digitalWrite(_chipSelect5, LOW);

	for (int i = 0; i < 16; i++)
	{
		_addressing(i);
	}

	digitalWrite(_chipSelect4, HIGH);
	digitalWrite(_chipSelect5, HIGH);
}


void Multiplex::writeChannel(int ch,int value)
{
	if (ch < 0 || ch > 32)
		return ;

	digitalWrite(_outsig, value);
	_addressing(ch);

	if(ch < 16)
		enableChip(_chipSelect4);
	else
		enableChip(_chipSelect5);
}


int Multiplex::readChannel(int ch)
{
	if (ch < 0 || ch > 47)
		return 0;

	if (ch < 16)
	{
		enableChip(_chipSelect1);
	}
	else if (ch >= 16 && ch < 32)
	{
		ch -= 16;
		enableChip(_chipSelect2);
	}
	else if (ch >= 32)
	{
		ch -= 32;
		enableChip(_chipSelect3);
	}

	_addressing(ch);
	return digitalRead(_sig);
}


bool Multiplex::Loop(int value)
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("Multiplex::Loop");
	#endif

	digitalWrite(_chipSelect1, HIGH);
	digitalWrite(_chipSelect2, HIGH);
	digitalWrite(_chipSelect3, HIGH);

	for (int ch = 0; ch < 16; ch++)
	{
		_addressing(ch);

		int read;
		digitalWrite(_chipSelect1, LOW);
		read = digitalRead(_sig);
		digitalWrite(_chipSelect1, HIGH);
		Input *input = m_pinball->GetInput(ch);
		if (input != NULL)
		{
			input->SetInput(read);
		}

		digitalWrite(_chipSelect2, LOW);
		read = digitalRead(_sig);
		digitalWrite(_chipSelect2, HIGH);
		input = m_pinball->GetInput(ch+16);
		if (input != NULL)
		{
			input->SetInput(read);
		}

		digitalWrite(_chipSelect3, LOW);
		read = digitalRead(_sig);
		digitalWrite(_chipSelect3, HIGH);
		input = m_pinball->GetInput(ch+32);
		if (input != NULL)
		{
			input->SetInput(read);
		}
	}
	return 0;
}


void Multiplex::_addressing(int ch)
{
	int i;
	for (i = 0; i < 4; i ++)
	{
		#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
			digitalWriteFast(_adrsPin[i],_muxChAddress[ch][i]);
		#else
			digitalWrite(_adrsPin[i],_muxChAddress[ch][i]);
		#endif
	}
}


