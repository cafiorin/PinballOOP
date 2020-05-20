#ifndef Playfield__INCLUDED_
#define Playfield__INCLUDED_

#include "Observer.h"

class Button;
class MultiplexInputs;
class LatchOutputs;
class BitOutput;
class LedControl;
class OutBall;
class KickoutHole;
class SlingShot;
class Target;
class DropTarget;
class Bumper;
class ReturnKickBall;
class AccumulatorBall;

class Playfield : public Observer
{
public:
	Playfield(MultiplexInputs* multiplexInputs,
		LatchOutputs* latchOutputsLow, LatchOutputs* LatchOutputsHigh, LedControl* ledControl);
	~Playfield();
	void onNotifySubject(EventType event, byte value);

private:
	MultiplexInputs* m_muxInputs;
	LatchOutputs* m_LatchOutputLowVoltage;
	LatchOutputs* m_LatchOutputHighVoltage;
	LedControl* m_LedControl;

	BitOutput* m_MotorSR;
	BitOutput* m_MotorRX;

	BitOutput* m_LedRamp;

	BitOutput* m_HEADLIGHT_SR;
	BitOutput* m_HEADLIGHT_RX;
	BitOutput* m_LockRampOn;
	BitOutput* m_LockRampOff;

	BitOutput* m_TurnFlipperOn;


	OutBall* m_OutBall;

	KickoutHole* m_Hole;

	SlingShot* m_SlingShotLeft;
	SlingShot* m_SlingShotRight ;

	Target* m_TargetOutLaneLeft;
	Target* m_TargetReturnBallLeft;
	Target* m_TargetReturnBallRight;
	Target* m_TargetOutLaneRight;
	Target* m_TargetGreen1;
	Target* m_TargetRed1;

	DropTarget* m_DropTarget5;
	DropTarget* m_DropTarget3;

	Bumper* m_BumperLeft;
	Bumper* m_BumperCenter;
	Bumper* m_BumperRight;
	ReturnKickBall* m_ReturnKickBall;
	AccumulatorBall* m_AccumulatorBall;

};
#endif
