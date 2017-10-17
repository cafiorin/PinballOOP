#ifndef StageBase__INCLUDED_
#define StageBase__INCLUDED_

#include "defines.h"
#include "Pinball.h"


class StageBase
{
public:
	StageBase(Pinball *pinball);
	virtual ~StageBase();

	void ShowStage(int stage);

protected:
	Pinball *m_Pinball;
};

#endif
