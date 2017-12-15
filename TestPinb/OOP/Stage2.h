/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage2__INCLUDED_
#define Stage2__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class SequencerLeds;

class Stage2 : public StageBase
{
public:
	Stage2(PinballMaster *pinball,int number);
	virtual ~Stage2();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	bool m_DropTargetOk;
	bool m_TargetsHigher;
	SequencerLeds *m_LedsHole, *m_LedsTargetHigher;

	void ResetStage();

};

#endif
