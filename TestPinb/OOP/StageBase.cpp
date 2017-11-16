#include "StageBase.h"
#include "PinballMaster.h"

StageBase::StageBase(PinballMaster *pinball, int number) : PinballObject("STAGE",pinball)
{
	m_PinballMaster = pinball;
	m_number = number;
}

StageBase::~StageBase()
{
}
