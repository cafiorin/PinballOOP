/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "SequencerLeds.h"
#include "PinballMaster.h"
#include "PinballObject.h"
#include "Timer.h"

// turnOn1by1 : Turn on and turn off last
// all : Turn on all (turn off all in the last)

//-----------------------------------------------------------
SequencerLeds::SequencerLeds(PinballMaster *pinball, SequencerType type,long time):PinballObject("SequencerLeds",pinball)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("SequencerLeds Constructor");
	#endif

	m_timerSeq = new Timer(time, "TimerSeq", pinball, this, TimerType::continuous);
	m_type = type;
	m_enabled = false;
	m_count = 0;
	m_pos = 0;
	m_blink = false;
}

//-----------------------------------------------------------
SequencerLeds::~SequencerLeds()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("SequencerLeds Destructor");
	#endif

	delete m_timerSeq;
}


//-----------------------------------------------------------
void SequencerLeds::AddLed(int led, bool turnOnWithNext)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("SequencerLeds::AddLed");
	#endif

	if (m_count < MAXLIGHTS)
	{
		LedControl *ledControl = m_pinball->GetLedControl();
		if (ledControl != NULL)
		{
			ledControl->TurnOff(led);
		}
		m_Leds[m_count] = led;
		m_LedsTurnOnWithNext[m_count] = turnOnWithNext;
		m_LedsAlwaysTurnOn[m_count] = false;
		m_count++;
	}
}

//-----------------------------------------------------------
void SequencerLeds::TurnOnAlwaysLed(int position,bool turnOn)
//-----------------------------------------------------------
{
	if (position < m_count)
	{
		m_LedsAlwaysTurnOn[position] = turnOn;
		LedControl *ledControl = m_pinball->GetLedControl();
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_Leds[position]);
		}
	}
}


//-----------------------------------------------------------
void SequencerLeds::RemoveLed(int led)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	LogMessage("SequencerLeds::RemoveLed");
	#endif

	bool found = false;
	if (m_count > 0)
	{
		for (char i = 0; i < m_count; i++)
		{
			if (m_Leds[i] == led)
			{
				found = true;
				LedControl *ledControl = m_pinball->GetLedControl();
				if (ledControl != NULL)
				{
					ledControl->TurnOn(led);
				}
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
	LogMessage("SequencerLeds::Start");
	#endif

	m_enabled = true;

	if (m_count > 0)
	{
		End();

		if (m_type != SequencerType::blinkingAll)
		{
			m_pos = 0;
			LedControl *ledControl = m_pinball->GetLedControl();
			if (ledControl != NULL)
			{
				ledControl->TurnOn(m_Leds[m_pos]);
				if (m_LedsTurnOnWithNext[m_pos])
				{
					m_pos = GetNext(m_pos);
					ledControl->TurnOn(m_Leds[m_pos]);
				}
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
	LogMessage("SequencerLeds::End");
	#endif

	m_pos = 0;
	LedControl *ledControl = m_pinball->GetLedControl();
	if (ledControl != NULL)
	{
		for (char i = 0; i < m_count; i++)
		{
			ledControl->TurnOff(m_Leds[i]);
		}
	}

}

//---------------------------------------------------------------------//
bool SequencerLeds::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("SequencerLeds::NotifyEvent");
	#endif

	// -- T I M E R  I S  O V E R --
	if (event == EVENT_TIMEISOVER)
	{
		return TimerIsOver(sender);
	}

	return false;
}


//---------------------------------------------------------------------//
bool SequencerLeds::TimerIsOver(PinballObject *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("SequencerLeds::TimerIsOver");
	#endif

	if (sender == m_timerSeq && m_enabled)
	{
		#ifdef DEBUGMESSAGES
		Debug("...Timer is over to seq");
		#endif

		LedControl *pLedControl = m_pinball->GetLedControl();
		if (pLedControl != NULL)
		{
			if (m_type == SequencerType::turnOnAndturnOff_1by1)
			{
				pLedControl->TurnOff(m_Leds[m_pos]);
				int posPrev = GetPrev(m_pos);
				if (m_LedsTurnOnWithNext[posPrev])
				{
					pLedControl->TurnOff(m_Leds[posPrev]);
				}

				m_pos = GetNext(m_pos);
				pLedControl->TurnOn(m_Leds[m_pos]);
				if (m_LedsTurnOnWithNext[m_pos])
				{
					m_pos = GetNext(m_pos);
					pLedControl->TurnOn(m_Leds[m_pos]);
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
					pLedControl->TurnOn(m_Leds[m_pos]);
					if (m_LedsTurnOnWithNext[m_pos])
					{
						m_pos = GetNext(m_pos);
						pLedControl->TurnOn(m_Leds[m_pos]);
					}
				}
			}
			else if (m_type == SequencerType::blinkingAll)
			{
				for (int i = 0; i < m_count; i++)
				{
					if (!m_LedsAlwaysTurnOn[i])
					{
						if (m_blink)
						{
							pLedControl->TurnOff(m_Leds[i]);
						}
						else
						{
							pLedControl->TurnOn(m_Leds[i]);
						}
					}
				}
				m_blink = !m_blink;
			}

			return true;
		}
	}

	return false;
}



