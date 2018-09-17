/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Input.h"
#include "Pinball.h"
#include "Event.h"

//-------------------------------------------------------//
Input::Input(uint8_t portNumber, PinballObject *pinballObjectParent):Port(portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Input Constructor"));
	#endif

	m_debounceRead = DEBOUNCEREAD;
	m_debounceCount = 0;
	m_InputValue = false;
	m_Edge = false;
	m_pinballObjectParent = pinballObjectParent;

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
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("Input::CheckDebounce"));
	#endif
	if (m_debounceCount > m_debounceRead)
	{
		m_debounceCount = 0;
		m_Edge = false;

		if (m_InputValue)
		{
			#ifdef DEBUGMESSAGES
			LogMessage(F("Input::Edge Positive"));
			#endif

			if (m_pinballObjectParent != NULL)
			{
				m_pinballObjectParent->NotifyEvent(this, &Event(EVENT_EDGEPOSITIVE));
			}
			else
			{
				m_Pinball->NotifyEvent(this, &Event(EVENT_EDGEPOSITIVE));
			}
			m_Pinball->PlaySongToInput(this->m_portNumber);
		}
		else
		{
			#ifdef DEBUGMESSAGES
			LogMessage(F("Input::Edge Negative"));
			#endif

			if (m_pinballObjectParent != NULL)
			{
				m_pinballObjectParent->NotifyEvent(this, &Event(EVENT_EDGENEGATIVE));
			}
			else
			{
				m_Pinball->NotifyEvent(this, &Event(EVENT_EDGENEGATIVE));
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
		m_debounceCount = 0;
		m_Edge = true;
	}

	if(m_Edge)
	{
		m_debounceCount++;
		CheckDebounce();
	}

	return newValue;
}
