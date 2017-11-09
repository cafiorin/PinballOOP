/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AttractMode.h"
#include "StageBase.h"
#include "Pinball.h"

//-----------------------------------------------------------
AttractMode::AttractMode(Pinball *pinball):StageBase(pinball)
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
}

//-----------------------------------------------------------
void AttractMode::Loop()
//-----------------------------------------------------------
{
}

