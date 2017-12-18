/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage4__INCLUDED_
#define Stage4__INCLUDED_

#include "defines.h"
#include "StageBase.h"
#include "SequencerLeds.h"
#include "Flag.h"

class Stage4 : public StageBase
{
public:
	Stage4(PinballMaster *pinball,int number);
	virtual ~Stage4();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsHole;
	Flag *m_Flags[MAX_FLAGS];
	int m_FlagCount;
	void ResetStage();

};

#endif
