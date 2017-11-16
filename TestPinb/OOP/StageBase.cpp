#include "StageBase.h"
#include "PinballMaster.h"

StageBase::StageBase(PinballMaster *pinball) : PinballObject("STAGE",pinball)
{
	m_Pinball = pinball;
}

StageBase::~StageBase()
{
}



