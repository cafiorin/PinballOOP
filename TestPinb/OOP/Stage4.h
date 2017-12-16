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
#define MAX_FLAGS 7

class Flag
{
public :
	Flag(int number)
	{
		m_number = number;
		m_captured = false;
		m_enableToCapture = false;
		m_Leds = NULL;
	}
	virtual ~Flag() {};
	void Disable()
	{
		m_enableToCapture = false;
		m_captured = false;
		if (m_Leds != NULL)
		{
			m_Leds->End();
		}
	}

	void EnableToCapture()
	{
		m_enableToCapture = true;
		m_captured = false;

		if (m_Leds != NULL)
		{
			m_Leds->Start();
		}
	}

	void Captured()
	{
		m_enableToCapture = false;
		m_captured = true;
		if (m_Leds != NULL)
		{
			m_Leds->End();
		}
	}

	int GetNumber() { return m_number; }
	SequencerLeds *m_Leds;
	bool IsCaptured() { return m_captured; }
private:
	int m_number;
	bool m_captured, m_enableToCapture;
};

class Stage4 : public StageBase
{
public:
	Stage4(PinballMaster *pinball,int number);
	virtual ~Stage4();

	virtual int PlayfieldEvent(PinballObject *sender, int event, int valueToSend);
	virtual void RestartPlayer();

	void Finished();

	SequencerLeds *m_LedsHole;
	Flag *m_Flags[MAX_FLAGS];
	int m_FlagCount;
	void ResetStage();

};

#endif
