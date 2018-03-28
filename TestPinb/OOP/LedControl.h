/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LedControl__INCLUDED_
#define LedControl__INCLUDED_

#include "defines.h"
#include "PinballObject.h"

#ifdef ARDUINOLIB
#include<FastLED.h>
#endif // ARDUINOLIB

#define NUM_LEDS 66
class PinballMaster;

class LedControl : public PinballObject
{
public:
	LedControl(PinballMaster *pinball);
	virtual ~LedControl();

	void TurnOn(uint8_t Led);
	void TurnOff(uint8_t Led);
	void TurnAll(bool turnOn);

	bool IsTurn(uint8_t Led) { return m_ledsValue[Led]; }
	void AttractModeLoop();

	#ifdef ARDUINOLIB
	CRGBArray<NUM_LEDS> m_leds;
	#endif
	bool m_ledsValue[NUM_LEDS];
};

#endif
