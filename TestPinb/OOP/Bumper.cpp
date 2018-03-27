/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Bumper.h"
#include "Input.h"
#include "Output.h"
#include "LedControl.h"
#include "PinballObject.h"
#include "PinballMaster.h"

//-------------------------------------------------------//
Bumper::Bumper(const char *szName, PinballMaster *pinball, int portNumberInput, int portNumberOutput,int LedNumber) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Bumper Constructor");
	#endif

	m_input = new Input("BperIn", pinball, portNumberInput,this);
	m_output = new Output("BperOut", pinball, portNumberOutput);
	m_Led = LedNumber;
	m_TimerLed = new Timer(200, "TBL", pinball, this, TimerType::once);
}

//-------------------------------------------------------//
Bumper::~Bumper()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("Bumper Destructor");
	#endif

	delete m_input;
	delete m_output;
}

//-------------------------------------------------------//
bool Bumper::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Bumper::NotifyEvent");
	#endif

	LedControl *ledControl = m_pinball->GetLedControl();
	if (event == EVENT_EDGEPOSITIVE)
	{
		m_output->TurnOnByTimer(TIME_COIL_ON);
		m_pinball->NotifyEvent(this, event, valueToSend);
		if (ledControl != NULL)
		{
			ledControl->TurnOn(m_Led);
		}
		m_TimerLed->Start();
		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		if (ledControl != NULL)
		{
			ledControl->TurnOff(m_Led);
		}
	}
	return false;
}

