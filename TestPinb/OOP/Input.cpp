/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Input.h"
#include "Pinball.h"

//-------------------------------------------------------//
Input::Input(const char *szName, Pinball *pinball, int portNumber, PinballObject *pinballObject):Port(pinball,szName,portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Input Constructor");
	#endif

	m_debounceRead = DEBOUNCEREAD;
	m_debounceCount = 0;
	m_InputValue = false;
	m_Edge = false;
	m_pinballObjectParent = pinballObject;

	m_pinball->AddPinballInput(this);
	//Init();
}

//-------------------------------------------------------//
Input::~Input()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Input Destructor");
	#endif
}

//-------------------------------------------------------//
bool Input::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Input::Init");
	#endif

	m_debounceCount = 0;

	return true;
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

			m_pinballObjectParent->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
		}
		else
		{
			#ifdef DEBUGMESSAGES
			Debug("Input::Edge Negative");
			#endif

			m_pinballObjectParent->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
		}

	}
}

//-------------------------------------------------------//
void Input::SetInput (bool value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Input::SetInput");
	#endif

	if (m_InputValue != value)
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
}
