/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Flag__INCLUDED_)
#define Flag__INCLUDED_

#include "defines.h"
#include "PinballObject.h"
#include "SequencerLeds.h"

#define MAX_FLAGS 7

class Flag
{
public:
	Flag(byte number)
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

	byte GetNumber() { return m_number; }
	SequencerLeds *m_Leds;
	bool IsCaptured() { return m_captured; }
private:
	byte m_number;
	bool m_captured, m_enableToCapture;
};


#endif // !defined(Port__INCLUDED_)
