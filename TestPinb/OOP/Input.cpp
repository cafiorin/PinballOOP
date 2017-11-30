/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Input.h"
#include "PinballMaster.h"

//-------------------------------------------------------//
Input::Input(const char *szName, PinballMaster *pinball, int portNumber, PinballObject *pinballObject):Port(pinball,szName,portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Input Constructor");
	#endif

	m_debounceRead = DEBOUNCEREAD;
	m_debounceCount = 0;
	m_InputValue = false;
	m_Edge = false;
	m_pinballObjectParent = pinballObject;

	m_pinball->AddPinballInput(this);
}

//-------------------------------------------------------//
Input::~Input()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Input Destructor");
	#endif
}

//-------------------------------------------------------//
bool Input::GetInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Input::GetInput");
	#endif

	return m_InputValue;
}

//-------------------------------------------------------//
void Input::CheckDebounce()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Input::CheckDebounce");
	#endif
	if (m_debounceCount > m_debounceRead)
	{
		m_debounceCount = 0;
		m_Edge = false;

		if (m_InputValue)
		{
			#ifdef DEBUGMESSAGES
			Debug("Input::Edge Positive");
			#endif

			if (m_pinballObjectParent != NULL)
			{
				m_pinballObjectParent->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
			}
			else
			{
				m_pinball->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
			}
			m_pinball->PlaySongToInput(this->m_portNumber);
		}
		else
		{
			#ifdef DEBUGMESSAGES
			Debug("Input::Edge Negative");
			#endif

			if (m_pinballObjectParent != NULL)
			{
				m_pinballObjectParent->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
			}
			else
			{
				m_pinball->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
			}
		}

	}
}

//-------------------------------------------------------//
bool Input::SetInput (bool value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Input::SetInput");
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
