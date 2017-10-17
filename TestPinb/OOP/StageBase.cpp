#include "StageBase.h"


StageBase::StageBase(Pinball *pinball)
{
	m_Pinball = pinball;
}

StageBase::~StageBase()
{
}

void StageBase::ShowStage(int stage)
{
	switch (stage)
	{
	case 0:
		//m_Pinball->
		// Turn on phase 0 in the playfield
		break;

	default:
		break;
	}
}


