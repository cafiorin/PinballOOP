#ifndef Stage0__INCLUDED_
#define Stage0__INCLUDED_

#include "defines.h"
#include "StageBase.h"

class Stage0 : public StageBase
{
public:
	Stage0(PinballMaster *pinball);
	virtual ~Stage0();
};

#endif
