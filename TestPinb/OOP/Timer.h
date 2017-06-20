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

protected:
	long m_time;
	long m_lastTime;  // the last time


};
#endif // !defined(Timer__INCLUDED_)
