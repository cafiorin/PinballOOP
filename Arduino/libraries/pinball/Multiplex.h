/*
	Chip CD4067 Multiplexer library
	S0,S1,S2,S3 = addressing
	SIG = output to an analog pin
	EN = Chip Selected


	Sample:

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

*/

#ifndef _MULTIPLEX_H_
#define _MULTIPLEX_H_

#ifdef ARDUINOLIB
#include "Arduino.h"
#endif

class Pinball;
class PinballObject;

class Multiplex : public PinballObject
{
 public:
	 Multiplex(Pinball *pinball, const int S0, const int S1, const int S2, const int S3, const int SIG, const int OUTSIG, const int chipSelect1, const int chipSelect2, const int chipSelect3, const int chipSelect4, const int chipSelect5);
	 void 			setup();
	 void			enableChip(int chipNumber);
	 int 			readChannel(int ch);
	 void			writeChannel(int ch, int value);
	 void			resetAllOutput();

	 virtual bool Loop(int value);

 private:
	 int	 _adrsPin[4];
	 int 	_sig;
	 int 	_outsig;

	 int 	_chipSelect1;
	 int 	_chipSelect2;
	 int 	_chipSelect3;
	 int 	_chipSelect4;
	 int 	_chipSelect5;

	 void 		_addressing(int ch);

};
#endif

