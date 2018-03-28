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
	Stage5(PinballMaster *pinball,uint8_t number);
	virtual ~Stage5();

	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsHole;
	Flag *m_Flags[MAX_FLAGS];
	uint8_t m_FlagCurrent, m_FlagCapturedCount;
	void ResetStage();

};

#endif
