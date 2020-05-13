#include "PinballMachine.h"
#include "LatchOutputs.h"
#include "MultiplexInputs.h"

#include "..\\OOP\\defines.h"

//----------------------------------------
PinballMachine::PinballMachine()
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


}
