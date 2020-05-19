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

#ifndef _MULTIPLEXINPUTS_H_
#define _MULTIPLEXINPUTS_H_

#include "defines.h"
#include "Runnable.h"
#include "BitInput.h"

#ifdef ARDUINOLIB
#include "Arduino.h"
#endif

class Observer;

class MultiplexInputs : public Runnable
{
public:
	MultiplexInputs(const byte S0, const byte S1, const byte S2, const byte S3,
		const byte SIGINPUT1, const byte SIGINPUT2, const byte SIGINPUT3);
	~MultiplexInputs();

	byte 	readChannel(byte ch);

	void loop();
	void AddInputObserverToEdgePositive(byte ch, Observer* observer);
	BitInput* GetInput(byte ch);

private:

	byte _adrsPin[4];
	byte _sigInput1;
	byte _sigInput2;
	byte _sigInput3;
	void _addressing(byte ch);
	BitInput* inputs[48];

};
#endif
