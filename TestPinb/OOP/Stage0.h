/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage0__INCLUDED_
#define Stage0__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class SequencerLeds;

class Stage0 : public StageBase
{
public:
	Stage0(PinballMaster *pinball,uint8_t number);
	virtual ~Stage0();

	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsStage;
	SequencerLeds *m_LedsTarget;
};

#endif
