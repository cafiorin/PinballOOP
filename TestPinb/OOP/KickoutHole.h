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
	KickoutHole(uint8_t portNumberInput, uint8_t portNumberOutput);
	virtual ~KickoutHole();
	virtual bool Init();
	virtual bool NotifyEvent(Object *sender, Event *event);

	void LanchBall();
	bool IsThereBall() { m_input->GetInput(); }

protected:
	Input *m_input;
	Output *m_output;

};
#endif // !defined(KickoutHole__INCLUDED_)
