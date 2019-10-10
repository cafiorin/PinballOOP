/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

#include "InputArduino.h"
#include "Pinball.h"

//-------------------------------------------------------//
InputArduino::InputArduino(uint8_t portNumber, PinballObject *parent):Port(portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("InputArduino Constructor"));
	#endif

	m_debounceRead = DEBOUNCEREAD;
	m_inputWithSameValueCount = 0;
	m_InputValue = false;
	m_Edge = false;
	m_parent = parent;

	#ifdef ARDUINOLIB
	pinMode(portNumber, INPUT);
	#endif

}

//-------------------------------------------------------//
InputArduino::~InputArduino()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("InputArduino Destructor"));
	#endif
}

//-------------------------------------------------------//
bool InputArduino::GetInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("InputArduino::GetInputArduino"));
	#endif

	#ifdef ARDUINOLIB
	m_InputValue = digitalRead(m_portNumber);
	#endif

	return m_InputValue;
}

//-------------------------------------------------------//
void InputArduino::CheckDebounce()
//-------------------------------------------------------//
{
	if (m_Enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("InputArduino::CheckDebounce"));
		#endif
		if (m_inputWithSameValueCount > m_debounceRead)
		{
			m_inputWithSameValueCount = 0;
			m_Edge = false;

			if (m_InputValue)
			{
				#ifdef DEBUGMESSAGES
				LogMessage(F("InputArduino::Edge Positive"));
				#endif

				if (m_parent != NULL)
				{
					m_parent->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
					m_Pinball->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
				}
				else
				{
					m_Pinball->NotifyEvent(this, EVENT_EDGEPOSITIVE, m_portNumber);
				}
				m_Pinball->PlaySongToInput(this->m_portNumber);
				
				#ifdef DOS
				m_InputValue = 0;
				#endif
			}
			else
			{
				#ifdef DEBUGMESSAGES
				LogMessage(F("InputArduino::Edge Negative"));
				#endif

				if (m_parent != NULL)
				{
					m_parent->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
					m_Pinball->NotifyEvent(this, EVENT_EDGENEGATIVE, m_portNumber);
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
bool InputArduino::SetInput (bool value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("InputArduino::SetInputArduino"));
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

//---------------------------------------------------------------------//
void InputArduino::Loop()
//---------------------------------------------------------------------//
{
	#ifdef ARDUINOLIB
	bool inputValue = digitalRead(m_portNumber);
	SetInput(inputValue);
	#endif
}
