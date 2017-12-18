/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage6__INCLUDED_
#define Stage6__INCLUDED_

#include "defines.h"
#include "StageBase.h"
#include "SequencerLeds.h"
#include "Flag.h"

class Stage6 : public StageBase
{
public:
	Stage6(PinballMaster *pinball,int number);
	virtual ~Stage6();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

	void Finished();

	SequencerLeds *m_LedsHole;
	Timer *m_TimerToCapture;
	Flag *m_Flags[MAX_FLAGS];
	int m_FlagCurrent, m_FlagCapturedCount;
	void ResetStage();

};

#endif
