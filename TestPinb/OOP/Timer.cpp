/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Timer.h"
#include "Pinball.h"

//-------------------------------------------------------//
Timer::Timer(unsigned long time, Object *parent, TimerType type,bool addToListPinball/*=true*/) : PinballObject(addToListPinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Timer Constructor"));
	#endif

	m_time = time;
	m_Enabled = false;
	m_parent = parent;
	m_type = type;
}

//-------------------------------------------------------//
Timer::~Timer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Timer Destructor"));
	#endif
}

//-------------------------------------------------------//
void Timer::Start()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Timer::Start"));
	#endif

	m_Enabled = true;
	m_lastTime = Millis();
}


//-------------------------------------------------------//
bool Timer::Check(unsigned long time /*=0 default*/)
//-------------------------------------------------------//
{
	if (m_Enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("Timer::Check"));
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

//-------------------------------------------------------//
void Timer::Loop()
//-------------------------------------------------------//
{
	if (m_Enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		LogMessage(F("Timer::Loop"));
		#endif

		if (Check())
		{
			if (m_parent != NULL)
			{
				m_parent->NotifyEvent(this, EVENT_TIMEISOVER,0);
			}
			else
			{
				m_Pinball->NotifyEvent(this, EVENT_TIMEISOVER,0);
			}

			if (m_type == TimerType::once)
			{
				m_Enabled = false;
			}

			m_lastTime = Millis();
		}
	}
}

