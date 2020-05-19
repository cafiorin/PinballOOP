/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SequencerLeds__INCLUDED_
#define SequencerLeds__INCLUDED_

#include "defines.h"
#include "Observer.h"

#define MAXLIGHTS 10

enum SequencerType
{
	turnOnAndturnOff_1by1,
	turnOn1by1_AndTurnOffAll,
	blinkingAll
};


class NewTimer;
class LedControl;

class SequencerLeds : public Observer
{
public:
	SequencerLeds(SequencerType type, unsigned long time, LedControl* ledControl);
	virtual ~SequencerLeds();

	void onNotifySubject(EventType event, byte value);

	void AddLed(byte led, bool turnOnWithNext = false);
	void RemoveLed(byte led);
	void Start();
	void End();

	byte m_Leds[MAXLIGHTS];
	bool m_LedsTurnOnWithNext[MAXLIGHTS];
	bool m_LedsAlwaysTurnOn[MAXLIGHTS];
	bool m_blink;
	byte m_count;
	byte m_pos;
	SequencerType m_type;

	byte GetPrev(byte pos)
	{
		if (pos - 1 < 0 )
			return m_count - 1;
		return pos - 1;
	}

	byte GetNext(byte led)
	{
		if (led + 1 >= m_count)
			return 0;
		return led + 1;
	}
	void TurnOnAlwaysLed(byte position, bool blink);

protected:
	NewTimer *m_timerSeq;
	LedControl* m_LedControl;
};

#endif
