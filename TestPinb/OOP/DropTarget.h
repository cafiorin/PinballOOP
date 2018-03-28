/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(DropTarget__INCLUDED_)
#define DropTarget__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Input.h"
#include "Output.h"

class SequencerLeds;

class DropTarget : public PinballObject
{
public:
	DropTarget(const char *szName, PinballMaster *pinball, uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberInput3, uint8_t portNumberOutput);
	DropTarget(const char *szName, PinballMaster *pinball, uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberInput3, uint8_t portNumberInput4, uint8_t portNumberInput5, uint8_t portNumberOutput);
	virtual ~DropTarget();
	virtual bool Init(StatusPinball status);
	virtual bool NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend);

	void Reset();
	bool IsAllTargets() { return m_AllTargets; }
	void AddLeds(uint8_t led1, uint8_t led2, uint8_t led3);
	void AddLeds(uint8_t led1, uint8_t led2, uint8_t led3,uint8_t led4,uint8_t led5);

protected:
	uint8_t m_sizeInputs;
	Input *m_input[5];
	Output *m_output;

	bool m_AllTargets;
	SequencerLeds *m_SequencerLeds;

};
#endif // !defined(DropTarget__INCLUDED_)
