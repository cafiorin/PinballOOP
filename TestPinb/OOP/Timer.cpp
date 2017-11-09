/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Timer.h"

//-------------------------------------------------------//
Timer::Timer(long time, const char *szName, Pinball *pinball) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Timer Constructor");
	#endif

	m_time = time;

	Init();
}

//-------------------------------------------------------//
Timer::~Timer()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Timer Destructor");
	#endif
}

//-------------------------------------------------------//
bool Timer::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Timer::Init");
	#endif
	
	m_enabled = true;
	m_lastTime = Millis();

	return true;
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


		if (ret)
			m_enabled = false;

		return ret;
	}

	return false;

}

//-------------------------------------------------------//
bool Timer::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("Timer::Loop");
		#endif

	}

	return false;
}

