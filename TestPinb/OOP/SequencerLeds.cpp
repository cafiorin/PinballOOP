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

//Kind = 0 : acende e apaga anterior
//Kind = 1 : acende na sequencia , apaga sรณ no final da sequencia de leds

//-----------------------------------------------------------
SequencerLeds::SequencerLeds(PinballMaster *pinball, SequencerType type,long time):PinballObject("SequencerLeds",pinball)
//-----------------------------------------------------------
{
	m_PinballMaster = pinball;
	m_timerSeq = new Timer(time, "TimerSeq", pinball, this, TimerType::continuous);
	m_type = type;
	m_enabled = false;
	m_count = 0;
	m_pos = 0;
}

//-----------------------------------------------------------
SequencerLeds::~SequencerLeds()
//-----------------------------------------------------------
{
	delete m_timerSeq;
}


//-----------------------------------------------------------
bool SequencerLeds::Init()
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGES
	Debug("SequencerLeds::Init");
	#endif

	return true;
}

//-----------------------------------------------------------
bool SequencerLeds::Loop(int value)
//-----------------------------------------------------------
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("SequencerLeds::Loop");
	#endif
	
	return false;
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
		m_Leds[m_count] = led;
		m_LedsTurnOnWithNext[m_count] = turnOnWithNext;
		m_count++;
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
		m_pos = 0;
		m_PinballMaster->m_LedControl->TurnOn(m_Leds[m_pos]);
		if (m_LedsTurnOnWithNext[m_pos])
		{
			m_pos = GetNext(m_pos);
			m_PinballMaster->m_LedControl->TurnOn(m_Leds[m_pos]);
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
	for (char i = 0; i < m_count; i++)
	{
		m_PinballMaster->m_LedControl->TurnOff(m_Leds[i]);
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
	if (sender == m_timerSeq && m_enabled)
	{
		#ifdef DEBUGMESSAGES
		Debug("...Timer is over to seq");
		#endif

		if (m_type == SequencerType::turnOn1by1)
		{
			m_PinballMaster->m_LedControl->TurnOff(m_Leds[m_pos]);
			int posPrev = GetPrev(m_pos);
			if (m_LedsTurnOnWithNext[posPrev])
			{
				m_PinballMaster->m_LedControl->TurnOff(m_Leds[posPrev]);
			}

			m_pos = GetNext(m_pos);
			m_PinballMaster->m_LedControl->TurnOn(m_Leds[m_pos]);
			if (m_LedsTurnOnWithNext[m_pos])
			{
				m_pos = GetNext(m_pos);
				m_PinballMaster->m_LedControl->TurnOn(m_Leds[m_pos]);
			}
		}
		else if (m_type == SequencerType::all)
		{
			m_pos = GetNext(m_pos);
			if (m_pos == 0)
			{
				Start();
			}
			else
			{
				m_PinballMaster->m_LedControl->TurnOn(m_Leds[m_pos]);
				if (m_LedsTurnOnWithNext[m_pos])
				{
					m_pos = GetNext(m_pos);
					m_PinballMaster->m_LedControl->TurnOn(m_Leds[m_pos]);
				}
			}
		}

		return true;
	}

	return false;
}



