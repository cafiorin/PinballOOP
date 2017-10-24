#ifdef ARDUINO

#include <Arduino.h>
#include "Multiplex.h"

static const uint8_t _muxChAddress[16][4] = {
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

Multiplex::Multiplex(const uint8_t S0,const uint8_t S1,const uint8_t S2,const uint8_t S3,const uint8_t SIG, const uint8_t OUTSIG, const uint8_t chipSelect1, const uint8_t chipSelect2, const uint8_t chipSelect3, const uint8_t chipSelect4, const uint8_t chipSelect5)
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

void Multiplex::enableChip(uint8_t chipNumber)
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

void Multiplex::init()
{
	uint8_t i;

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

void Multiplex::resetAllOutput()
{
	digitalWrite(_outsig, LOW);

	digitalWrite(_chipSelect4, LOW);
	digitalWrite(_chipSelect5, LOW);

	for (i = 0; i < 16; i++)
	{
		_addressing(ch);
	}

	digitalWrite(_chipSelect4, HIGH);
	digitalWrite(_chipSelect5, HIGH);
}


void Multiplex::writeChannel(bool enableChip4, uint8_t ch,int value)
{
	if (ch < 0 || ch > 15)
		return 0;

	digitalWrite(_outsig, value);
	_addressing(ch);

	if(enableChip4)
		enableChip(_chipSelect4);
	else
		enableChip(_chipSelect5);
}


int Multiplex::readChannel(uint8_t ch)
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


void Multiplex::_addressing(uint8_t ch)
{
	uint8_t i;
	for (i = 0; i < 4; i ++)
	{
		#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
			digitalWriteFast(_adrsPin[i],_muxChAddress[ch][i]);
		#else
			digitalWrite(_adrsPin[i],_muxChAddress[ch][i]);
		#endif
	}
}

#endif
