/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(KickoutHole__INCLUDED_)
#define KickoutHole__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

class KickoutHole : public PinballObject
{
public:
	KickoutHole(const char *szName, PinballMaster *pinball, uint8_t portNumberInput, uint8_t portNumberOutput);
	virtual ~KickoutHole();
	virtual bool Init(StatusPinball status);
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);

	void LanchBall();
	bool IsThereBall() { return m_ball; }

protected:
	Input *m_input1;
	Output *m_output;
	bool m_ball;

};
#endif // !defined(KickoutHole__INCLUDED_)
