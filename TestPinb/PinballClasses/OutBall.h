/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(OutBall__INCLUDED_)
#define OutBall__INCLUDED_

#include "Observer.h"
#include "BitInput.h"
#include "Initializable.h"

class BitOutput;
class Subject;

#define MAX_PINBALLBALL 4

class OutBall : public Observer, public Initializable
{
public:
	OutBall(BitInput* input1, BitOutput* output1, BitInput* input2, BitOutput* output2);

	//virtual
	virtual ~OutBall();
	void init();
	void onNotifySubject(EventType event, byte value);

	void LanchBall();
	byte GetBalls() { return m_nBalls; }
	bool IsThereAnyBallInGame() { return (m_nBalls < MAX_PINBALLBALL); }
	void AddObserverToLostBall(Observer* observer);

protected:
	BitInput *m_input1;
	BitOutput *m_output1;
	BitInput *m_input2;
	BitOutput *m_output2;
	byte m_nBalls;

	void AddBall() { (m_nBalls + 1) > MAX_PINBALLBALL ? m_nBalls = MAX_PINBALLBALL : m_nBalls++; }
	void RemoveBall() { (m_nBalls - 1) <= 0 ? m_nBalls = 0 : m_nBalls--; }

	Subject* m_EventToLostBall;

};
#endif // !defined(OutBall__INCLUDED_)
