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

class DropTarget : public PinballObject
{
public:
	DropTarget(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberInput2, int portNumberInput3, int portNumberOutput);
	DropTarget(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberInput2, int portNumberInput3, int portNumberInput4, int portNumberInput5, int portNumberOutput);
	virtual ~DropTarget();
	virtual bool Init();
	virtual bool Loop(int value);

	void Reset();
	bool IsAllTargets() { return m_AllTargets; }

protected:
	int m_sizeInputs;
	Input *m_input[5];
	Output *m_output;

	bool m_AllTargets;

};
#endif // !defined(DropTarget__INCLUDED_)
