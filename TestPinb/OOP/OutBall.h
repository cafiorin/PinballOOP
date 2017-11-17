/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(OutBall__INCLUDED_)
#define OutBall__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

#define MAX_PINBALLBALL 4

class OutBall : public PinballObject
{
public:
	OutBall(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberOutput1, int portNumberInput2, int portNumberOutput2, Multiplex *multiplex);
	virtual ~OutBall();
	virtual bool Init();
	virtual bool Loop(int value);
	virtual bool NotifyEvent(PinballObject *sender, int event, int valueToSend);

	void LanchBall();
	int GetBalls() { return m_nBalls; }
	bool IsThereAnyBallInGame() { return (m_nBalls < MAX_PINBALLBALL); }

protected:
	Input *m_input1;
	Output *m_output1;
	Input *m_input2;
	Output *m_output2;
	int m_nBalls;

	void AddBall() { (m_nBalls + 1) > MAX_PINBALLBALL ? m_nBalls = MAX_PINBALLBALL : m_nBalls++; }
	void RemoveBall() { (m_nBalls - 1) <= 0 ? m_nBalls = 0 : m_nBalls--; }

};
#endif // !defined(OutBall__INCLUDED_)
