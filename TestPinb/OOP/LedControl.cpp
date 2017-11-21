/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "LedControl.h"
#include "PinballMaster.h"
#include "PinballObject.h"

#ifdef ARDUINOLIB
#include<FastLED.h>
#endif // ARDUINOLIB


//-----------------------------------------------------------
LedControl::LedControl(PinballMaster *pinball):PinballObject("LedControl",pinball)
//-----------------------------------------------------------
{
	#ifdef ARDUINOLIB
	FastLED.addLeds<WS2812B, DATA_STRIP_LED, GRB>(m_leds, NUM_LEDS);
	#endif // ARDUINOLIB

	for (int i = 0; i < NUM_LEDS; i++)
	{
		TurnOff(i);
	}
}

//-----------------------------------------------------------
LedControl::~LedControl()
//-----------------------------------------------------------
{
}


//-----------------------------------------------------------
bool LedControl::Init()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("LedControl::Init");
	#endif

	for (int i = 0; i < NUM_LEDS; i++)
	{
		TurnOff(i);
	}

	return true;
}

//-----------------------------------------------------------
void LedControl::TurnOn(int Led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("LedControl::TurnOn");
	#endif

	m_ledsValue[Led] = true;

	#ifdef ARDUINOLIB
	m_leds[Led] = CRGB::White;
	FastLED.show();
	#endif
}

//-----------------------------------------------------------
void LedControl::TurnOff(int Led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("LedControl::TurnOff");
	#endif

	m_ledsValue[Led] = false;

	#ifdef ARDUINOLIB
	m_leds[Led] = CRGB::Black;
	FastLED.show();
	#endif

}

//-----------------------------------------------------------
void LedControl::Loop()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("LedControl::Loop");
	#endif


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

