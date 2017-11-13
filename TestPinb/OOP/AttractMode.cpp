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
AttractMode::AttractMode(PinballMaster *pinball):StageBase(pinball)
//-----------------------------------------------------------
{
}

//-----------------------------------------------------------
AttractMode::~AttractMode()
//-----------------------------------------------------------
{
}


//-----------------------------------------------------------
void AttractMode::Init()
//-----------------------------------------------------------
{
	m_Pinball->sendMessageToAnotherArduino(ADDRESS_SLAVE, INIT_THEME);
	m_Pinball->printText("PRESS", "START", 0);
}

//-----------------------------------------------------------
void AttractMode::Loop()
//-----------------------------------------------------------
{
	m_Pinball->m_LedControl->Loop();
}

