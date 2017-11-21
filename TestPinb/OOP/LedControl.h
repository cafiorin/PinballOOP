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

	virtual bool Init();
	virtual void Loop();

	void TurnOn(int Led);
	void TurnOff(int Led);
	bool IsTurn(int Led) { return m_ledsValue[Led]; }
	#ifdef ARDUINOLIB
	CRGBArray<NUM_LEDS> m_leds;
	#endif
	bool m_ledsValue[NUM_LEDS];
};

#endif
