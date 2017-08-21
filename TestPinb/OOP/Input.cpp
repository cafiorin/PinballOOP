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
	#ifdef DEBUGMESSAGES
	Debug("Input Constructor");
	#endif
	m_portNumber = portNumber;
	m_TimerDebounce = new Timer(m_debounceDelay, "TimerD", pinball);
	m_debounceDelay = 50;

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

	#ifdef ARDUINO
	return (digitalRead(m_portNumber) == LOW);
	#endif

	#ifdef DOS
	if (m_emulateInput)
	{
		m_emulateInput=false;
		return true;
	}

	return false;
	#endif
}

//-------------------------------------------------------//
bool Input::CheckEdgePositive()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("Input::CheckEdgePositive");
	#endif

  if(m_enabled)
  {
	  bool edge = false;
	  bool reading = GetInput();

	  // If the input changed, due to noise or pressing:
	  if (reading != m_lastState && reading == true && m_lastState == false) 
	  {
		  if (m_TimerDebounce->Check())
		  {
			  // if input state has changed:
			  edge = true;
		  }
		  // reset the debouncing timer
		  m_TimerDebounce->Init();
	  }

	  m_lastState = reading;
	  return edge;
  }
  return false;
}

//-------------------------------------------------------//
bool Input::Loop(int value)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGESLOOP
	Debug("Input::Loop");
#endif

#ifdef DOS
	if (m_portNumber == value) 
		m_emulateInput = !m_emulateInput;
#endif

	return false;
}
