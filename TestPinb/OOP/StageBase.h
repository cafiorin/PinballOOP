#ifndef StageBase__INCLUDED_
#define StageBase__INCLUDED_

#include "defines.h"
#include "pinballobject.h"

class PinballMaster;

class StageBase : public PinballObject
{
public:
	StageBase(PinballMaster *pinball, int number);
	virtual ~StageBase();
	int GetNumber() { return m_number; }

protected:
	PinballMaster *m_PinballMaster;
	int m_number;
};

#endif
