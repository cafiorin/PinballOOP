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

	m_portNumber = portNumber;
	m_TimerDebounce = new Timer(m_debounceDelay, "TimerD", pinball);
	m_debounceDelay = 50;
	m_InputValue = false;
	m_pinballObjectParent = pinballObject;

	Init();
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

	m_TimerDebounce->Init();

	return true;
}

//-------------------------------------------------------//
bool Input::GetInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Input::GetInput");
	#endif

	if (m_InputValue)
	{
		m_InputValue = false;
		return true;
	}

	return false;
}

//-------------------------------------------------------//
void Input::SetInput (bool value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Input::SetInput");
	#endif

	if (m_InputValue != value)
	{
		if (m_TimerDebounce->Check())
		{
			if (m_InputValue)
			{
				#ifdef DEBUGMESSAGES
				Debug("Input::Edge Positive");
				#endif

				m_pinballObjectParent->NotifyEvent(m_portNumber, EVENT_EDGEPOSITIVE);
			}
			else
			{
				#ifdef DEBUGMESSAGES
				Debug("Input::Edge Negative");
				#endif

				m_pinballObjectParent->NotifyEvent(m_portNumber, EVENT_EDGENEGATIVE);
			}

			m_InputValue = value;
			m_TimerDebounce->Init();
		}
	}
}

//-------------------------------------------------------//
bool Input::Loop(int value)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGESLOOP
	Debug("Input::Loop");
#endif

	return false;
}
