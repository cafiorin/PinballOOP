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
	Stage4(PinballMaster *pinball,uint8_t number);
	virtual ~Stage4();

	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsHole;
	Flag *m_Flags[MAX_FLAGS];
	uint8_t m_FlagCount;
	void ResetStage();

};

#endif
