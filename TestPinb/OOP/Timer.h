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

class Timer : public PinballObject
{
public:
	Timer(long time, const char *szName, Pinball *pinball);
	virtual ~Timer();
	virtual bool Init();
	virtual bool Loop(int value);

	bool Check(long time=0);
	void ChangeValue(long time) 
	{ 
		m_time = time; 
		Init();
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
