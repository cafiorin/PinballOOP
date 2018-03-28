/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef Stage6__INCLUDED_
#define Stage6__INCLUDED_

#include "defines.h"
#include "StageBase.h"
#include "SequencerLeds.h"
#include "Flag.h"

class Stage6 : public StageBase
{
public:
	Stage6(PinballMaster *pinball,uint8_t number);
	virtual ~Stage6();

	virtual uint8_t PlayfieldEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	virtual void RestartPlayer();
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);

	void Finished();

	SequencerLeds *m_LedsHole;
	Timer *m_TimerToCapture;
	Flag *m_Flags[MAX_FLAGS];
	uint8_t m_FlagCurrent, m_FlagCapturedCount;
	void ResetStage();

};

#endif
