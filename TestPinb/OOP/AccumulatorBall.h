/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(AccumulatorBall__INCLUDED_)
#define AccumulatorBall__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

class AccumulatorBall : public PinballObject
{
public:
	AccumulatorBall(const char *szName, PinballMaster *pinball, int portNumberInput1, int portNumberInput2, int portNumberInput3, int portNumberInput4, int portNumberOutput);

	virtual ~AccumulatorBall();
	virtual bool Init();
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);
	int GetNumberBalls() {return m_nBalls;}
	void LanchBall();

protected:
	Input *m_input1;
	Input *m_input2;
	Input *m_input3;
	Input *m_input4;
	Output *m_output;

	int m_nBalls;
};
#endif // !defined(AccumulatorBall__INCLUDED_)
