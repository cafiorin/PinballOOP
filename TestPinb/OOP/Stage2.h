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
	Stage2(PinballMaster *pinball,uint8_t number);
	virtual ~Stage2();

	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	virtual void RestartPlayer();

	void Finished();

	bool m_DropTargetOk;
	bool m_TargetsHigher;
	SequencerLeds *m_LedsHole, *m_LedsTargetHigher;

	void ResetStage();

};

#endif
