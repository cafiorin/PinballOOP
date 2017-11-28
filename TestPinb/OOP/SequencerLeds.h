/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SequencerLeds__INCLUDED_
#define SequencerLeds__INCLUDED_

#include "defines.h"
#include "PinballObject.h"

#define MAXLIGHTS 10

enum SequencerType
{
	turnOnAndturnOff_1by1,
	turnOn1by1_AndTurnOffAll,
	blinkingAll
};


class PinballMaster;
class Timer;

class SequencerLeds : public PinballObject
{
public:
	SequencerLeds(PinballMaster *pinball, SequencerType type, long time);
	virtual ~SequencerLeds();

	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

	bool TimerIsOver(PinballObject *sender);
	void AddLed(int led, bool turnOnWithNext = false);
	void RemoveLed(int led);
	void Start();
	void End();

	int m_Leds[MAXLIGHTS];
	bool m_LedsTurnOnWithNext[MAXLIGHTS];
	bool m_LedsAlwaysTurnOn[MAXLIGHTS];
	bool m_blink;
	char m_count;
	char m_pos;
	SequencerType m_type;

	int GetPrev(int pos)
	{
		if (pos - 1 < 0 )
			return m_count - 1;
		return pos - 1;
	}

	int GetNext(int led)
	{
		if (led + 1 >= m_count)
			return 0;
		return led + 1;
	}
	void TurnOnAlwaysLed(int position, bool blink);

protected:
	Timer *m_timerSeq;



};

#endif
