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
	#ifdef DEBUGMESSAGESCREATION
	Debug("LedControl Constructor");
	#endif

	m_enabled = false;
	
	if (m_enabled)
	{
		#ifdef ARDUINOLIB
		FastLED.addLeds<WS2812B, DATA_STRIP_LED, GRB>(m_leds, LED_LAST);
		#endif // ARDUINOLIB
	}

	for (int i = 0; i <= NUM_LEDS; i++)
	{
		TurnOff(i);
	}
}

//-----------------------------------------------------------
LedControl::~LedControl()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("LedControl Destructor");
	#endif

}

//-----------------------------------------------------------
void LedControl::TurnAll(bool turnOn)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("LedControl::TurnOnAll");
	#endif

	for (int i = LED_FIRST; i <= LED_LAST; i++)
	{
		m_ledsValue[i] = turnOn;
		if (m_enabled)
		{
			#ifdef ARDUINOLIB
			m_leds[i] = turnOn ? CRGB::White : CRGB::Black;
			#endif
		}
	}
	if (m_enabled)
	{
		#ifdef ARDUINOLIB
		FastLED.show();
		#endif
	}

}

//-----------------------------------------------------------
void LedControl::TurnOn(int Led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("LedControl::TurnOn");
	#endif
	
	if (Led < NUM_LEDS)
	{
		m_ledsValue[Led] = true;

		if (m_enabled)
		{
			#ifdef ARDUINOLIB
			m_leds[Led] = CRGB::White;
			FastLED.show();
			#endif
		}
	}
}

//-----------------------------------------------------------
void LedControl::TurnOff(int Led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("LedControl::TurnOff");
	#endif
	if (Led < NUM_LEDS)
	{
		m_ledsValue[Led] = false;

		if (m_enabled)
		{
			#ifdef ARDUINOLIB
			m_leds[Led] = CRGB::Black;
			FastLED.show();
			#endif
		}
	}

}

//-----------------------------------------------------------
void LedControl::AttractModeLoop()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("LedControl::AttractModeLoop");
	#endif

	if (m_enabled)
	{
		#ifdef ARDUINOLIB
		static uint8_t hue;
		for (int i = 0; i <= LED_LAST / 2; i++)
		{
			// fade everything out
			m_leds.fadeToBlackBy(40);

			// let's set an led value
			m_leds[i] = CHSV(hue++, 255, 255);

			// now, let's first 20 leds to the top 20 leds, 
			m_leds(LED_LAST / 2, LED_LAST - 1) = m_leds(LED_LAST / 2 - 1, 0);
			FastLED.delay(33);
		}
		#endif
	}
}
