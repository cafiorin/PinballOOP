#include "PinballMachine.h"
#include "LatchOutputs.h"
#include "MultiplexInputs.h"
#include "Door.h"
#include "Observer.h"

#include "..\\OOP\\defines.h"

//----------------------------------------
PinballMachine::PinballMachine() : Observer()
//----------------------------------------
{
	CreateObjects();
}


//----------------------------------------
PinballMachine::~PinballMachine()
//----------------------------------------
{

}

//----------------------------------------
void PinballMachine::CreateObjects()
//----------------------------------------
{
	m_muxInputs = new MultiplexInputs(/*S0*/23, /*S1*/25, /*S2*/27,/*S3*/29, /*SIn0*/22, /*SIn1*/34, /*SIn2*/36);
	m_LatchOutputLowVoltage = new LatchOutputs(A4, A5, A3);
	m_LatchOutputHighVoltage = new LatchOutputs(A8, A9, A10); // TODO: Fix this values
	m_Door = new Door(this);
}

//---------------------------------------------------------------------
void PinballMachine::onNotifySubject(const Subject*, EventType event, byte value)
//---------------------------------------------------------------------
{
	switch (event)
	{
	case EventType::Pressed:
		ButtonPressed(value);
		break;
	
	default:
		break;
	}
}

//---------------------------------------------------------------------
void PinballMachine::ButtonPressed(byte value)
//---------------------------------------------------------------------
{
	switch (value)
	{
	case INPUT_MENU_BUTTON:
		break;
	case INPUT_UP_BUTTON:
		break;
	case INPUT_DOWN_BUTTON:
		break;
	case INPUT_ENTER_BUTTON:
		break;
	default:
		break;
	}
}
