/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Light__INCLUDED_)
#define Light__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Timer.h"
#include "Output.h"

class Light : public Output
{
public:
	Light(const char *szName, Pinball *pinball, int portNumber, Multiplex *multiplex);
	virtual ~Light();
	virtual bool Init();
	virtual bool Loop(int value);

	void StartBlink(long value=700);
	void EndBlink();

protected:
	Timer *m_timerBlinking;
};
#endif 
