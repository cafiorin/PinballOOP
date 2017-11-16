/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AttractMode.h"
#include "StageBase.h"
#include "PinballMaster.h"

//-----------------------------------------------------------
AttractMode::AttractMode(PinballMaster *pinball):StageBase(pinball,-1)
//-----------------------------------------------------------
{
}

//-----------------------------------------------------------
AttractMode::~AttractMode()
//-----------------------------------------------------------
{
}


//-----------------------------------------------------------
bool AttractMode::Init()
//-----------------------------------------------------------
{
	m_PinballMaster->sendMessageToAnotherArduino(ADDRESS_SLAVE, INIT_THEME);
	m_PinballMaster->printText("PRESS", "START", 0);

	return true;
}

//-----------------------------------------------------------
void AttractMode::Loop()
//-----------------------------------------------------------
{
	m_PinballMaster->m_LedControl->Loop();
}

