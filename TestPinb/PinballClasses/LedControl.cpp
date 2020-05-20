/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "LedControl.h"
#include "Logger.h"

#ifdef ARDUINOLIB
#include<FastLED.h>
#endif // ARDUINOLIB


//-----------------------------------------------------------
LedControl::LedControl()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("LedControl Constructor"));
	#endif

	#ifdef ARDUINOLIB
	FastLED.addLeds<WS2812B, DATA_STRIP_LED, GRB>(m_leds, LED_LAST);
	#endif // ARDUINOLIB

	for (byte i = 0; i <= NUM_LEDS; i++)
	{
		TurnOff(i);
	}
}

//-----------------------------------------------------------
void LedControl::TurnAll(bool turnOn)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("LedControl::TurnOnAll"));
	#endif

	for (byte i = LED_FIRST; i <= LED_LAST; i++)
	{
		m_ledsValue[i] = turnOn;
		#ifdef ARDUINOLIB
		m_leds[i] = turnOn ? CRGB::White : CRGB::Black;
		#endif
	}

	#ifdef ARDUINOLIB
	FastLED.show();
	#endif

}

//-----------------------------------------------------------
void LedControl::TurnOn(byte Led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("LedControl::TurnOn"));
	#endif
	
	if (Led < NUM_LEDS)
	{
		m_ledsValue[Led] = true;

		#ifdef ARDUINOLIB
		m_leds[Led] = CRGB::White;
		FastLED.show();
		#endif
	}
}

//-----------------------------------------------------------
void LedControl::TurnOff(byte Led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("LedControl::TurnOff"));
	#endif
	if (Led < NUM_LEDS)
	{
		m_ledsValue[Led] = false;

		#ifdef ARDUINOLIB
		m_leds[Led] = CRGB::Black;
		FastLED.show();
		#endif
	}

}

//-----------------------------------------------------------
void LedControl::AttractModeLoop()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	Logger::LogMessage(F"LedControl::AttractModeLoop");
	#endif

	#ifdef ARDUINOLIB
	static byte hue;
	for (byte i = 0; i <= LED_LAST / 2; i++)
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
