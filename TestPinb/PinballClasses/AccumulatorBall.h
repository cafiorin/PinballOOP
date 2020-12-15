/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(AccumulatorBall__INCLUDED_)
#define AccumulatorBall__INCLUDED_

#include "Observer.h"
#include "Initializable.h"

class MultiplexInputs;
class LatchOutputs;
class Subject;
class BitOutput;
class BitInput;

class AccumulatorBall : public Observer, public Initializable
{
public:
	AccumulatorBall(byte portNumberInput1, byte portNumberInput2, 
		byte portNumberInput3, byte portNumberInput4, 
		byte portNumberOutput, MultiplexInputs* inputs,
		LatchOutputs* outputHighVoltage);

	virtual ~AccumulatorBall();
	byte GetNumberBalls() {return m_nBalls;}
	void VerifyNumberOfBalls();
	void LanchBall();

//virtual
	void init();
	void onNotifySubject(EventType event, byte value);

protected:
	byte m_nBalls;
	BitOutput* m_output;
	BitInput* m_input1;
	BitInput* m_input2;
	BitInput* m_input3;
	BitInput* m_input4;
};
#endif // !defined(AccumulatorBall__INCLUDED_)
