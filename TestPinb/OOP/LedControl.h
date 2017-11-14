#ifndef LedControl__INCLUDED_
#define LedControl__INCLUDED_

#include "defines.h"
#include "StageBase.h"

#ifdef ARDUINOLIB
#include<FastLED.h>
#endif // ARDUINOLIB

#define NUM_LEDS 66

class LedControl : public StageBase
{
public:
	LedControl(int dataPin, PinballMaster *pinball);
	virtual ~LedControl();

	virtual void Init();
	virtual void Loop();

	void TurnOn(int Led);
	void TurnOff(int Led);

	#ifdef ARDUINOLIB
	CRGBArray<NUM_LEDS> m_leds;
	#endif

};

#endif
