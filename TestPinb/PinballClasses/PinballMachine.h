#ifndef PinballMachine__INCLUDED_
#define PinballMachine__INCLUDED_

class MultiplexInputs;
class LatchOutputs;

class PinballMachine
{
public :
	PinballMachine();
	~PinballMachine();

private :
	void CreateObjects();
	MultiplexInputs* m_muxInputs;
	LatchOutputs* m_LatchOutputLowVoltage;
	LatchOutputs* m_LatchOutputHighVoltage;

	//Door with buttons
	//Display
	//Playfield
	//Som
	
	//Display debug e buttons debug
	//Serial output debug

	//PinballGame
	//Players


};

#endif
