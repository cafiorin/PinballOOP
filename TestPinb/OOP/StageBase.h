#ifndef StageBase__INCLUDED_
#define StageBase__INCLUDED_

#include "defines.h"
#include "pinballobject.h"

class PinballMaster;

class StageBase : public PinballObject
{
public:
	StageBase(PinballMaster *pinball);
	virtual ~StageBase();

	virtual bool Init() {return true;}
	virtual void Loop() {};

protected:
	PinballMaster *m_Pinball;
};

#endif
