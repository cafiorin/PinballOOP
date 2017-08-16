/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(DropTargetWithRemoteInput__INCLUDED_)
#define DropTargetWithRemoteInput__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "RemoteInput.h"
#include "Output.h"

class DropTargetWithRemoteInput : public PinballObject
{
public:
	DropTargetWithRemoteInput(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberInput2, int portNumberInput3, int portNumberOutput);
	DropTargetWithRemoteInput(const char *szName, Pinball *pinball, int portNumberInput1, int portNumberInput2, int portNumberInput3, int portNumberInput4, int portNumberInput5, int portNumberOutput);
	virtual ~DropTargetWithRemoteInput();
	virtual bool Init();
	virtual bool Loop(int value);

	void Reset();
	bool IsAllTargets() { return m_AllTargets; }

protected:
	int m_sizeInputs;
	RemoteInput *m_input[5];
	Output *m_output;

	bool m_AllTargets;

};
#endif // !defined(DropTargetWithRemoteInput__INCLUDED_)
