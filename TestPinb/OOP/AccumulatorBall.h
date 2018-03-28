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
	AccumulatorBall(const char *szName, PinballMaster *pinball, uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberInput3, uint8_t portNumberInput4, uint8_t portNumberOutput);

	virtual ~AccumulatorBall();
	virtual bool Init(StatusPinball status);
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);
	uint8_t GetNumberBalls() {return m_nBalls;}
	void LanchBall();

protected:
	Input *m_input1;
	Input *m_input2;
	Input *m_input3;
	Input *m_input4;
	Output *m_output;

	uint8_t m_nBalls;
};
#endif // !defined(AccumulatorBall__INCLUDED_)
