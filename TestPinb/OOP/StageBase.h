#ifndef StageBase__INCLUDED_
#define StageBase__INCLUDED_

#include "defines.h"

class Pinball;

class StageBase
{
public:
	StageBase(Pinball *pinball);
	virtual ~StageBase();

	virtual void Init() {};
	virtual void Loop() {};

protected:
	Pinball *m_Pinball;
};

#endif
