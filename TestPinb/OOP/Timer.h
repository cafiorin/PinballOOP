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
	Timer(unsigned long time, Object *parent=NULL, TimerType type=TimerType::once, bool addToListPinball=true);
	virtual ~Timer();
	virtual void Loop();
	Object *m_parent;
	TimerType m_type;

	void Start();
	bool Check(unsigned long time=0);
	void ChangeTimerValue(unsigned long time) 
	{ 
		m_time = time; 
	}

protected:
	#ifdef DOS
	clock_t m_time;
	clock_t m_lastTime;  // the last time
	#endif
	
	#ifdef ARDUINOLIB
	unsigned long m_time;
	unsigned long m_lastTime;  // the last time
	#endif
};
#endif // !defined(Timer__INCLUDED_)
