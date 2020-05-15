#ifndef PinballMachine__INCLUDED_
#define PinballMachine__INCLUDED_

#include "Observer.h"

class MultiplexInputs;
class LatchOutputs;
class Door;

class PinballMachine : public Observer
{
public :
	PinballMachine();
	~PinballMachine();

protected:
	void onNotifySubject(const Subject*, EventType event, byte value);
	void ButtonPressed(byte value);

private :
	void CreateObjects();
	MultiplexInputs* m_muxInputs;
	LatchOutputs* m_LatchOutputLowVoltage;
	LatchOutputs* m_LatchOutputHighVoltage;
	Door* m_Door;

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
