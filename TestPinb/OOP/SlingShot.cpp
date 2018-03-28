/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defines.h"
#include "SlingShot.h"
#include "PinballMaster.h"
#include "PinballObject.h"
#include "DefinesMp3.h"

//-------------------------------------------------------//
SlingShot::SlingShot(const char *szName, PinballMaster *pinball, uint8_t portNumberInput1, uint8_t portNumberInput2, uint8_t portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("SlingShot Constructor");
	#endif

	m_input1 = new Input("SLIn1", pinball, portNumberInput1, this);
	m_input2 = new Input("SLIn2", pinball, portNumberInput2, this);
	
	m_output = new Output("SLOut", pinball, portNumberOutput);
}

//-------------------------------------------------------//
SlingShot::~SlingShot()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("SlingShot Destructor");
	#endif

	delete m_input1;
	delete m_input2;
	delete m_output;
}

//-------------------------------------------------------//
bool SlingShot::Init(StatusPinball status)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("SlingShot Init");
	#endif

	if (!m_input1->GetInput() && !m_input2->GetInput())
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------//
bool SlingShot::NotifyEvent(PinballObject *sender, uint8_t event, uint8_t valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Slingshot::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		m_output->TurnOnByTimer(TIME_COIL_ON);
		m_pinball->NotifyEvent(this, event, valueToSend);
		return true;
	}
	return false;
}
