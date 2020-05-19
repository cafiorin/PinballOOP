/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LedControl__INCLUDED_
#define LedControl__INCLUDED_

#include "defines.h"

#ifdef ARDUINOLIB
#include<FastLED.h>
#endif // ARDUINOLIB

#define NUM_LEDS 66

class LedControl
{
public:
	LedControl();

	void TurnOn(byte Led);
	void TurnOff(byte Led);
	void TurnAll(bool turnOn);

	bool IsTurn(byte Led) { return m_ledsValue[Led]; }
	void AttractModeLoop();

	#ifdef ARDUINOLIB
	CRGBArray<NUM_LEDS> m_leds;
	#endif
	bool m_ledsValue[NUM_LEDS];
};

#endif
