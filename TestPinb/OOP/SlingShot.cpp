/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "SlingShot.h"
#include "Pinball.h"
#include "PinballObject.h"
#include "DefinesMp3.h"

//-------------------------------------------------------//
SlingShot::SlingShot(uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberOutput) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("SlingShot Constructor"));
	#endif

	m_input1 = new Input(portNumberInput1, this);
	m_input2 = new Input(portNumberInput2, this);
	
	m_output = new Output(portNumberOutput);
}

//-------------------------------------------------------//
SlingShot::~SlingShot()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("SlingShot Destructor"));
	#endif

	/*
	delete m_input1;
	delete m_input2;
	delete m_output;
	*/
}

//-------------------------------------------------------//
bool SlingShot::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("SlingShot Init"));
	#endif

	if (!m_input1->GetInput() && !m_input2->GetInput())
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------//
bool SlingShot::NotifyEvent(Object *sender, uint8_t event, uint8_t value)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Slingshot::NotifyEvent"));
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_output->TurnOnByTimer(TIME_COIL_ON);
		m_Pinball->NotifyEvent(sender, event, value);
		return true;
	}
	return false;
}
