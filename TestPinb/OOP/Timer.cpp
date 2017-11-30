/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Timer.h"
#include "PinballMaster.h"

//-------------------------------------------------------//
Timer::Timer(long time, const char *szName, PinballMaster *pinball, PinballObject *parent, TimerType type) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Timer Constructor");
	#endif

	m_time = time;
	m_enabled = false;
	m_parent = parent;
	m_type = type;
}

//-------------------------------------------------------//
Timer::~Timer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Timer Destructor");
	#endif
}

//-------------------------------------------------------//
void Timer::Start()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Timer::Start");
	#endif

	m_enabled = true;
	m_lastTime = Millis();
}


//-------------------------------------------------------//
bool Timer::Check(long time /*=0 default*/)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("Timer::Check");
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
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("Timer::Loop");
		#endif

		if (Check())
		{
			if (m_parent != NULL)
			{
				m_parent->NotifyEvent(this, EVENT_TIMEISOVER, 0);
			}
			else
			{
				m_pinball->NotifyEvent(this, EVENT_TIMEISOVER, 0);
			}

			if (m_type == TimerType::once)
			{
				m_enabled = false;
			}

			m_lastTime = Millis();
		}
	}
}

