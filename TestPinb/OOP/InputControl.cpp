/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "InputControl.h"
#include "Pinball.h"
#include "Multiplex.h"

//-------------------------------------------------------//
InputControl::InputControl(const char *szName, Pinball *pinball, Multiplex *multiplex):PinballObject(szName,pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("InputControl Constructor");
	#endif
	
	m_multiplex = multiplex;
	
	Init();
}

//-------------------------------------------------------//
InputControl::~InputControl()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("InputControl Destructor");
	#endif
}

//-------------------------------------------------------//
bool InputControl::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("InputControl::Init");
	#endif

	return true;
}


//-------------------------------------------------------//
bool InputControl::Loop(int value)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGESLOOP
	Debug("InputControl::Loop");
#endif

	return false;
}
