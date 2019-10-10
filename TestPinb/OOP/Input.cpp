/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Input.h"
#include "Pinball.h"
#include "Timer.h"

//-------------------------------------------------------//
Input::Input(uint8_t portNumber, PinballObject *parent):Port(portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Input Constructor"));
	#endif

	m_debounceRead = DEBOUNCEREAD;
	m_inputWithSameValueCount = 0;
	m_QuantDebouncePerSecond = 0;
	m_NumberTriesDebounce = 0;
	m_InputValue = false;
	m_Edge = false;
	m_parent = parent;
	m_timer = new Timer(1000, this, TimerType::continuous, true);
	m_timer->Enable();

	m_Pinball->AddPinballInput(this);
}

//-------------------------------------------------------//
Input::~Input()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Input Destructor"));
	#endif
}

//-------------------------------------------------------//
bool Input::GetInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("Input::GetInput"));
	#endif

	return m_InputValue;
}

//-------------------------------------------------------//
void Input::CheckDebounce()
//-------------------------------------------------------//
{
	if (m_Enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("Input::CheckDebounce"));
		#endif
		if (m_inputWithSameValueCount > m_debounceRead)
		{
			m_inputWithSameValueCount = 0;
			m_Edge = false;

			if (m_InputValue)
			{
				#ifdef DEBUGMESSAGES
				LogMessage(F("Input::Edge Positive"));
				#endif

				if (m_parent != NULL)
				{
					m_parent->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
					//m_Pinball->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
					if (m_timer->IsEnabled())
					{
						m_QuantDebouncePerSecond++;
					}
				}
				else
				{
					m_Pinball->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
				}
				m_Pinball->PlaySongToInput(this->m_portNumber);
			}
			else
			{
				#ifdef DEBUGMESSAGES
				LogMessage(F("Input::Edge Negative"));
				#endif

				if (m_parent != NULL)
				{
					m_parent->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
					//m_Pinball->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
				}
				else
				{
					m_Pinball->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
				}
			}

		}
	}
}

//-------------------------------------------------------//
bool Input::SetInput (bool value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("Input::SetInput"));
	#endif

	bool newValue = (m_InputValue != value);
	if (newValue)
	{
		m_InputValue = value;
		m_inputWithSameValueCount = 0;
		m_Edge = true;
	}

	if(m_Edge)
	{
		m_inputWithSameValueCount++;
		CheckDebounce();
	}

	return newValue;
}

//-------------------------------------------------------//
bool Input::NotifyEvent(Object* /*sender*/, uint8_t event, uint8_t /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Light::NotifyEvent"));
	#endif

	if (event == EVENT_TIMEISOVER)
	{
		if (m_QuantDebouncePerSecond >= MAX_DEBOUNCE_PER_SECOND)
		{ 
			m_Enabled = false; // Yes disable it! This input with error input
			m_timer->Disable();
		}
		else
		{
			m_QuantDebouncePerSecond = 0;
			m_NumberTriesDebounce++;
		}

		if (m_NumberTriesDebounce >= MAX_TRY_DEBOUNCES)
		{
			m_timer->Disable();
		}
		return true;
	}

	return false;
}
