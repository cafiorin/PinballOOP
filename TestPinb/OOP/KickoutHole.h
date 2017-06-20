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
	KickoutHole(const char *szName, Pinball *pinball, int portNumberInput, int portNumberOutput);
	virtual ~KickoutHole();
	virtual bool Init();
	virtual bool Loop(int value);

	void LanchBall();
	bool IsThereBall() { return m_ball; }

protected:
	Input *m_input1;
	Output *m_output;
	bool m_ball;

};
#endif // !defined(KickoutHole__INCLUDED_)
