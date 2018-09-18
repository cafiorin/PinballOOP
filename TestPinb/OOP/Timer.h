/* BSD 3 - Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Timer__INCLUDED_)
#define Timer__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "PinballObject.h"

enum TimerType
{
	once,
	continuous
};

class Timer : public PinballObject
{
public:
	Timer(long time, PinballObject *parent=NULL, TimerType type=TimerType::once);
	virtual ~Timer();
	virtual void Loop();
	PinballObject *m_parent;
	TimerType m_type;

	void Start();
	bool Check(long time=0);
	void ChangeTimerValue(long time) 
	{ 
		m_time = time; 
	}

protected:
	#ifdef DOS
	clock_t m_time;
	clock_t m_lastTime;  // the last time
	#endif
	
	#ifdef ARDUINOLIB
	long m_time;
	long m_lastTime;  // the last time
	#endif
};
#endif // !defined(Timer__INCLUDED_)
