/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Input.h"

//-------------------------------------------------------//
Input::Input(const char *szName, Pinball *pinball, int portNumber):Port(pinball,szName,portNumber)
//-------------------------------------------------------//
{
	m_debounceDelay=50;
	
	#ifdef DEBUGMESSAGES
	Debug("Input Constructor");
	#endif
	
	#ifdef DOS
	m_emulateInput = false;
	#endif

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

	#ifdef ARDUINO
	pinMode(m_portNumber, INPUT);
	#endif

	m_startReading = false;
	m_lastState = GetInput();
	m_lastDebounceTime = Millis();

	return true;
}

//-------------------------------------------------------//
bool Input::GetInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Input::GetInput");
	#endif

	#ifdef ARDUINO
	return (digitalRead(m_portNumber) == LOW);
	#endif

	#ifdef DOS
	return m_emulateInput;
	#endif
}

//-------------------------------------------------------//
bool Input::CheckEdgePositive()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Input::CheckEdgePositive");
	#endif

  bool edge = false;
  if(m_enabled)
  {
	  bool reading = GetInput();

	  // If the input changed, due to noise or pressing:
	  if (reading != m_lastState && reading == true && m_lastState == false) 
	  {
		// reset the debouncing timer
		m_lastDebounceTime = Millis();
		m_startReading = true;
	  }

	  if (m_startReading && ((Millis() - m_lastDebounceTime) > m_debounceDelay)) 
	  {
		// if input state has changed:
		if (reading == true) 
		{
			edge = true;
		}
		m_startReading = false;
	  }

	  m_lastState = reading;
  }
  return edge;
}

