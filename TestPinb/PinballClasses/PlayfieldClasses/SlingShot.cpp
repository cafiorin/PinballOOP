/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SlingShot.h"
#include "..\\BitInput.h"
#include "..\\BitOutput.h"
#include "..\\Observer.h"
#include "..\\Subject.h"
#include "..\\EventType.h"
#include "..\\Utils.h"
#include "..\\Logger.h"

//-------------------------------------------------------//
SlingShot::SlingShot(BitInput* input1, BitInput* input2, BitOutput* output) : Observer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SlingShot Constructor"));
	#endif

	m_EventToSlingShotActivated = NULL;

	m_input1 = input1;
	m_input2 = input2;
	
	m_output = output;
}

//-------------------------------------------------------//
SlingShot::~SlingShot()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("SlingShot Destructor"));
	#endif

	delete m_EventToSlingShotActivated;
}

//-------------------------------------------------------//
void SlingShot::onNotifySubject(EventType event, byte /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("Slingshot::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		m_output->Pulse();
	}
}

//------------------------------------------------//
void SlingShot::AddObserverToSlingShotActivated(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToSlingShotActivated == NULL)
	{
		m_EventToSlingShotActivated = new Subject(EventType::SlingShotActivated);
	}

	m_EventToSlingShotActivated->registerObserver(observer);
}

