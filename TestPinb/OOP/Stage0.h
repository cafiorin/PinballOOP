#ifndef Stage0__INCLUDED_
#define Stage0__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class SequencerLeds;

class Stage0 : public StageBase
{
public:
	Stage0(PinballMaster *pinball,int number);
	virtual ~Stage0();

	virtual bool Init();
	virtual bool Loop(int);

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsStage;
	SequencerLeds *m_LedsTarget;
};

#endif
