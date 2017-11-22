#ifndef SequencerLeds__INCLUDED_
#define SequencerLeds__INCLUDED_

#include "defines.h"
#include "PinballObject.h"

#define MAXLIGHTS 20

enum SequencerType
{
	turnOn1by1,
	all
};


class PinballMaster;
class Timer;

class SequencerLeds : public PinballObject
{
public:
	SequencerLeds(PinballMaster *pinball, SequencerType type, long time);
	virtual ~SequencerLeds();

	virtual bool Init();
	virtual bool Loop(int value);
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

	bool TimerIsOver(PinballObject *sender);
	void AddLed(int led, bool turnOnWithNext = false);
	void Start();
	void End();

	int m_Leds[MAXLIGHTS];
	bool m_LedsTurnOnWithNext[MAXLIGHTS];
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

protected:
	PinballMaster *m_PinballMaster;
	Timer *m_timerSeq;

};

#endif
