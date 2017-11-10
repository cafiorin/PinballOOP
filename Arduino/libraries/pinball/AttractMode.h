#ifndef AttractMode__INCLUDED_
#define AttractMode__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class AttractMode : public StageBase
{
public:
	AttractMode(PinballMaster *pinball);
	virtual ~AttractMode();

	virtual void Init();
	virtual void Loop();

};

#endif
