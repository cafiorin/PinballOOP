/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage3__INCLUDED_
#define Stage3__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class SequencerLeds;

class Stage3 : public StageBase
{
public:
	Stage3(PinballMaster *pinball,int number);
	virtual ~Stage3();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	bool m_DropTarget3, m_DropTarget5;
	bool m_TargetsHigher;
	bool m_RampOut2;

	SequencerLeds *m_LedsHole, *m_LedsTargetHigher,*m_LedsRamp;

	void ResetStage();

};

#endif
