/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SequencerLeds.h"
#include "NewTimer.h"
#include "LedControl.h"
#include "Observer.h"
#include "Logger.h"

#include "defines.h"


// turnOn1by1 : Turn on and turn off last
// all : Turn on all (turn off all in the last)

//-----------------------------------------------------------
SequencerLeds::SequencerLeds(SequencerType type, unsigned long time, LedControl* ledControl):Observer()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SequencerLeds Constructor"));
	#endif
	m_LedControl = ledControl;
	m_timerSeq = new NewTimer(time, NewTimerType::continuous, this);
	m_type = type;
	m_count = 0;
	m_pos = 0;
	m_blink = false;
}

//-----------------------------------------------------------
SequencerLeds::~SequencerLeds()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SequencerLeds Destructor"));
	#endif

	delete m_timerSeq;
}


//-----------------------------------------------------------
void SequencerLeds::AddLed(byte led, bool turnOnWithNext)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SequencerLeds::AddLed"));
	#endif

	if (m_count < MAXLIGHTS)
	{
		m_LedControl->TurnOff(led);
		m_Leds[m_count] = led;
		m_LedsTurnOnWithNext[m_count] = turnOnWithNext;
		m_LedsAlwaysTurnOn[m_count] = false;
		m_count++;
	}
}

//-----------------------------------------------------------
void SequencerLeds::TurnOnAlwaysLed(byte position,bool turnOn)
//-----------------------------------------------------------
{
	if (position < m_count)
	{
		m_LedsAlwaysTurnOn[position] = turnOn;
		m_LedControl->TurnOn(m_Leds[position]);
	}
}


//-----------------------------------------------------------
void SequencerLeds::RemoveLed(byte led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SequencerLeds::RemoveLed"));
	#endif

	bool found = false;
	if (m_count > 0)
	{
		for (byte i = 0; i < m_count; i++)
		{
			if (m_Leds[i] == led)
			{
				found = true;
				m_LedControl->TurnOn(led);
			}

			if (found && (i + 1 < m_count))
			{
				m_Leds[i] = m_Leds[i + 1];
			}

		}
		m_count--;
	}
}

//-----------------------------------------------------------
void SequencerLeds::Start()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SequencerLeds::Start"));
	#endif

	if (m_count > 0)
	{
		End();

		if (m_type != SequencerType::blinkingAll)
		{
			m_pos = 0;
			m_LedControl->TurnOn(m_Leds[m_pos]);
			if (m_LedsTurnOnWithNext[m_pos])
			{
				m_pos = GetNext(m_pos);
				m_LedControl->TurnOn(m_Leds[m_pos]);
			}
		}

		m_timerSeq->Start();
	}
}

//-----------------------------------------------------------
void SequencerLeds::End()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SequencerLeds::End"));
	#endif

	m_pos = 0;
	for (byte i = 0; i < m_count; i++)
	{
		m_LedControl->TurnOff(m_Leds[i]);
	}

}

//---------------------------------------------------------------------//
void SequencerLeds::onNotifySubject(EventType /*event*/, byte /*value*/)
//---------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("SequencerLeds::NotifyEvent"));
#endif

	// -- T I M E R  I S  O V E R --
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("...Timer is over to seq"));
#endif

	if (m_type == SequencerType::turnOnAndturnOff_1by1)
	{
		m_LedControl->TurnOff(m_Leds[m_pos]);
		byte posPrev = GetPrev(m_pos);
		if (m_LedsTurnOnWithNext[posPrev])
		{
			m_LedControl->TurnOff(m_Leds[posPrev]);
		}

		m_pos = GetNext(m_pos);
		m_LedControl->TurnOn(m_Leds[m_pos]);
		if (m_LedsTurnOnWithNext[m_pos])
		{
			m_pos = GetNext(m_pos);
			m_LedControl->TurnOn(m_Leds[m_pos]);
		}
	}
	else if (m_type == SequencerType::turnOn1by1_AndTurnOffAll)
	{
		m_pos = GetNext(m_pos);
		if (m_pos == 0)
		{
			Start();
		}
		else
		{
			m_LedControl->TurnOn(m_Leds[m_pos]);
			if (m_LedsTurnOnWithNext[m_pos])
			{
				m_pos = GetNext(m_pos);
				m_LedControl->TurnOn(m_Leds[m_pos]);
			}
		}
	}
	else if (m_type == SequencerType::blinkingAll)
	{
		for (byte i = 0; i < m_count; i++)
		{
			if (!m_LedsAlwaysTurnOn[i])
			{
				if (m_blink)
				{
					m_LedControl->TurnOff(m_Leds[i]);
				}
				else
				{
					m_LedControl->TurnOn(m_Leds[i]);
				}
			}
		}
		m_blink = !m_blink;
	}
}



