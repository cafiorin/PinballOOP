/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
	Chip CD4067 Multiplexer library
	S0,S1,S2,S3 = addressing
	SIG = output to an analog pin
	EN = Chip Selected
	
	Sample:	
	{
		Multiplex plex = Multiplex(3,4,5,6,A0,10,11,12);
	
		void setup()
		{
		  plex.begin();
		}

		void loop()
		{
		  plex.readChannel(0); //it read the channel 0 from chip 1
		  plex.writeChannel(3,LOW);//write LOW to channel 3
		}
	}

*/

#ifndef _MULTIPLEX_H_
#define _MULTIPLEX_H_

#include "defines.h"

#ifdef ARDUINOLIB
#include "Arduino.h"
#endif

class PinballObject;

class Multiplex : public PinballObject
{
 public:
	 Multiplex(const uint8_t S0, const uint8_t S1, const uint8_t S2, const uint8_t S3, const uint8_t SIG, const uint8_t OUTSIG, const uint8_t SIG1, const uint8_t SIG2, const uint8_t chipSelect1, const uint8_t chipSelect2, const uint8_t chipSelect3, const uint8_t chipSelect4, const uint8_t chipSelect5);
	 void 		setup();
	 void		enableChip(uint8_t chipNumber);
	 uint8_t 	readChannel(uint8_t ch);
	 void		writeChannel(uint8_t ch, uint8_t value);
	 void		resetAllOutput();

	 virtual void Loop();

 private:
	 int		_adrsPin[4];
	 uint8_t 	_sig;
	 uint8_t 	_sig1;
	 uint8_t 	_sig2;
	 uint8_t 	_outsig;

	 uint8_t 	_chipSelect1;
	 uint8_t 	_chipSelect2;
	 uint8_t 	_chipSelect3;
	 uint8_t 	_chipSelect4;
	 uint8_t 	_chipSelect5;

	 void 		_addressing(uint8_t ch);
};
#endif

