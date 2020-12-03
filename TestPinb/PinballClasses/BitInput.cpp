/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "utils.h"
#include "BitInput.h"
#include "Observer.h"
#include "Subject.h"
#include "Logger.h"

#define DEBOUNCE_TO_EDGE 50

//-------------------------------------------------------//
BitInput::BitInput(byte portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::Logger::LogMessage(F("BitInput Constructor"));
	#endif

	m_portNumber = portNumber;
	m_inputValueOld = HIGH;
	m_inputValue = HIGH;
	m_EventEdgePositive = NULL;
}

//-------------------------------------------------------//
BitInput::~BitInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::Logger::LogMessage(F("BitInput Destructor"));
	#endif

	delete m_EventEdgePositive;
}

//------------------------------------------------//
bool BitInput::GetInput()
//------------------------------------------------//
{
	return m_inputValue;
}

//------------------------------------------------//
void BitInput::AddObserverToEdgePositive(Observer* observer)
//------------------------------------------------//
{
	if (m_EventEdgePositive == NULL)
	{
		m_EventEdgePositive = new Subject(EventType::EdgePositive, m_portNumber);
	}

	m_EventEdgePositive->registerObserver(observer);
}

//------------------------------------------------//
void BitInput::loop()
//------------------------------------------------//
{
	if (m_EventEdgePositive == NULL)
		return;

	bool prevState = m_inputValueOld;
	m_inputValue = GetInput();
	if (prevState == HIGH && m_inputValue == LOW)
	{
		buttonDownMs = Millis();
	}
	else if (prevState == LOW && m_inputValue == HIGH)
	{
		if (Millis() - buttonDownMs > DEBOUNCE_TO_EDGE)
		{
			m_EventEdgePositive->notifyObserver();
			m_inputValueOld = m_inputValue;
		}
	}
}

