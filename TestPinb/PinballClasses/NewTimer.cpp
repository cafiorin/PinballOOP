/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "..\\OOP\\defines.h"
#include "..\\OOP\\utils.h"
#include "NewTimer.h"
#include "Runnable.h"
#include "Subject.h"

//-------------------------------------------------------//
NewTimer::NewTimer(unsigned long time, NewTimerType type) : Runnable()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("NewTimer Constructor"));
	#endif

	m_time = time;
	m_enabled = false;
	m_type = type;
}

//-------------------------------------------------------//
NewTimer::~NewTimer()
//-------------------------------------------------------//
{
}

//-------------------------------------------------------//
void NewTimer::Start()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("NewTimer::Start"));
	#endif

	m_enabled = true;
	m_lastTime = Millis();
}


//-------------------------------------------------------//
bool NewTimer::Check(unsigned long time /*=0 default*/)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("NewTimer::Check"));
		#endif

		bool ret = false;

		#ifdef ARDUINOLIB
		if (time == 0)
			ret = ((Millis() - m_lastTime) > m_time);
		else
			ret = ((Millis() - m_lastTime) > time);
		#endif

		#ifdef DOS
		if (time == 0)
			ret = (timediff(Millis() , m_lastTime) > m_time);
		else
			ret = (timediff(Millis() , m_lastTime) > time);
		#endif

		return ret;
	}

	return false;

}

//------------------------------------------------//
void NewTimer::AddObserverToTimeIsOver(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToTimeIsOver == NULL)
	{
		m_EventToTimeIsOver = new Subject(EventType::TimeIsOver, 0);
	}

	m_EventToTimeIsOver->registerObserver(observer);
}

//-------------------------------------------------------//
void NewTimer::loop()
//-------------------------------------------------------//
{
	if (m_enabled && m_EventToTimeIsOver != NULL)
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("NewTimer::Loop"));
		#endif

		if (Check())
		{
			m_EventToTimeIsOver->notifyObserver();

			if (m_type == NewTimerType::once)
			{
				m_enabled = false;
			}

			m_lastTime = Millis();
		}
	}
}

