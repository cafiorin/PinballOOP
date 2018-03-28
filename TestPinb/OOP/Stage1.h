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
	Stage1(PinballMaster *pinball,uint8_t number);
	virtual ~Stage1();

	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	virtual void RestartPlayer();

	void Finished();

	bool m_DropTargetOk;
	bool m_Targets[3];
	SequencerLeds *m_LedsHole;

	void ResetStage();

};

#endif
