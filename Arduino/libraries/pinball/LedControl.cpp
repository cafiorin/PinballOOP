/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "LedControl.h"
#include "pinball.h"

#ifdef ARDUINOLIB
#include<FastLED.h>
#endif // ARDUINOLIB


//-----------------------------------------------------------
LedControl::LedControl(int dataPin, PinballMaster *pinball):StageBase(pinball)
//-----------------------------------------------------------
{
	#ifdef ARDUINOLIB
	FastLED.addLeds<WS2812B, 5, GRB>(m_leds, NUM_LEDS);
	#endif // ARDUINOLIB
}

//-----------------------------------------------------------
LedControl::~LedControl()
//-----------------------------------------------------------
{
}


//-----------------------------------------------------------
void LedControl::Init()
//-----------------------------------------------------------
{
}

//-----------------------------------------------------------
void LedControl::Loop()
//-----------------------------------------------------------
{

	#ifdef ARDUINOLIB
	static uint8_t hue;
	for (int i = 0; i < NUM_LEDS / 2; i++)
	{
		// fade everything out
		m_leds.fadeToBlackBy(40);

		// let's set an led value
		m_leds[i] = CHSV(hue++, 255, 255);

		// now, let's first 20 leds to the top 20 leds, 
		m_leds(NUM_LEDS / 2, NUM_LEDS - 1) = m_leds(NUM_LEDS / 2 - 1, 0);
		FastLED.delay(33);
	}
	#endif

}

