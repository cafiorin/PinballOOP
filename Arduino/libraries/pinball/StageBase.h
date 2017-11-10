#ifndef StageBase__INCLUDED_
#define StageBase__INCLUDED_

#include "defines.h"

class PinballMaster;

class StageBase
{
public:
	StageBase(PinballMaster *pinball);
	virtual ~StageBase();

	virtual void Init() {};
	virtual void Loop() {};

protected:
	PinballMaster *m_Pinball;
};

#endif
