/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage5__INCLUDED_
#define Stage5__INCLUDED_

#include "defines.h"
#include "StageBase.h"
#include "SequencerLeds.h"
#include "Flag.h"

class Stage5 : public StageBase
{
public:
	Stage5(PinballMaster *pinball,int number);
	virtual ~Stage5();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsHole;
	Flag *m_Flags[MAX_FLAGS];
	int m_FlagCurrent, m_FlagCapturedCount;
	void ResetStage();

};

#endif
