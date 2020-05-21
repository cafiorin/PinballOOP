/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(DropTarget__INCLUDED_)
#define DropTarget__INCLUDED_

#include "..\\Observer.h"
#include "..\\Initializable.h"
#include "..\\ChangeableStatus.h"

class SequencerLeds;
class BitOutput;
class BitInput;
class Subject;
class LedControl;

class DropTarget : public Observer, public Initializable, public ChangeableStatus

{
public:
	DropTarget(BitInput* input1, BitInput* input2, BitInput* input3, BitOutput* output, LedControl* ledControl);
	DropTarget(BitInput* input1, BitInput* input2, BitInput* input3, BitInput* input4, BitInput* input5, BitOutput* output, LedControl* ledControl);
	void AddObserverToDropTargeComplete(Observer* observer);

//virtual
	virtual ~DropTarget();
	void init();
	void onNotifySubject(EventType event, byte value);
	void changeStatus(StatusPinballMachine status);

	void Reset();
	bool IsAllTargets() { return m_AllTargets; }
	void AddLeds(byte led1, byte led2, byte led3);
	void AddLeds(byte led1, byte led2, byte led3,byte led4,byte led5);

protected:
	byte m_sizeInputs;
	BitInput *m_input[5];
	BitOutput *m_output;
	Subject* m_EventToDropTargetComplete;

	bool m_AllTargets;
	SequencerLeds *m_SequencerLeds;

private:
	void Initialize(byte sizeInputs, BitInput* input1, BitInput* input2, BitInput* input3,
		BitInput* input4, BitInput* input5, BitOutput* output, LedControl* ledControl);

};
#endif // !defined(DropTarget__INCLUDED_)
