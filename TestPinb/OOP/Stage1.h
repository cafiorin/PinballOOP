/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage1__INCLUDED_
#define Stage1__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class SequencerLeds;

class Stage1 : public StageBase
{
public:
	Stage1(PinballMaster *pinball,int number);
	virtual ~Stage1();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	bool m_DropTargetOk;
};

#endif
