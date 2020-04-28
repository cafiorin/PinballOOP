/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\\OOP\\utils.h"
#include "BitInput.h"
#include "Observer.h"
#include "Subject.h"

//-------------------------------------------------------//
BitInput::BitInput(byte portNumber)
//-------------------------------------------------------//
{
	m_portNumber = portNumber;
	m_inputValue = HIGH;
	m_EventEdgePositive = NULL;

#ifdef ARDUINOLIB
	pinMode(m_portNumber, INPUT_PULLUP);
	m_inputValue = digitalRead(pin);
#endif
}

//------------------------------------------------//
bool BitInput::GetInput()
//------------------------------------------------//
{
#ifdef ARDUINOLIB
	m_inputValue = digitalRead(m_portNumber);
#endif

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

	int prevState = m_inputValue;
	m_inputValue = GetInput();
	if (prevState == HIGH && m_inputValue == LOW)
	{
		buttonDownMs = Millis();
	}
	else if (prevState == LOW && m_inputValue == HIGH)
	{
		if (Millis() - buttonDownMs < 50)
		{
			// ignore this for debounce
		}
		else if (m_EventEdgePositive != NULL)
		{
			m_EventEdgePositive->notifyObserver();
		}
	}
}

