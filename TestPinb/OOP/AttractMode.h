/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef AttractMode__INCLUDED_
#define AttractMode__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class Timer;

class AttractMode : public StageBase
{
public:
	AttractMode(PinballMaster *pinball);
	virtual ~AttractMode();

	virtual bool Init();
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

	void InitGameOver();

private:
	Timer *m_timerGameOver;
	bool TimerIsOver(PinballObject *sender);
	bool m_showGameOver;
	bool m_showAlternate;

};

#endif
