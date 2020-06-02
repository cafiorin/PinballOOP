/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Bumper.h"
#include "Observer.h"
#include "BitInput.h"
#include "BitOutput.h"
#include "Subject.h"
#include "Logger.h"

//-------------------------------------------------------//
Bumper::Bumper(BitInput* input, BitOutput* output, BitOutput* ledOutput):Observer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("Bumper Constructor"));
	#endif

	m_input = input;
	m_input->AddObserverToEdgePositive(this);
	m_output = output;
	m_Led = ledOutput;
	m_EventToBumperActivated = NULL;
}

//-------------------------------------------------------//
Bumper::~Bumper()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("Bumper Destructor"));
	#endif

	delete m_EventToBumperActivated;
}

//-------------------------------------------------------//
void Bumper::onNotifySubject(EventType event, byte /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("Bumper::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		m_output->Pulse();
		m_Led->TurnOnByTimer(500);
		if (m_EventToBumperActivated != NULL)
			m_EventToBumperActivated->notifyObserver();
	}
}

//------------------------------------------------//
void Bumper::AddObserverToBumperActivated(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToBumperActivated == NULL)
	{
		m_EventToBumperActivated = new Subject(EventType::BumperActivated);
	}

	m_EventToBumperActivated->registerObserver(observer);
}
