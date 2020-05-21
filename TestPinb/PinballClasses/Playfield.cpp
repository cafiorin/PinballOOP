#include "Playfield.h"
#include "LatchOutputs.h"
#include "MultiplexInputs.h"
#include "Button.h"
#include "BitOutput.h"
#include "LedControl.h"
#include "PlayfieldClasses\\OutBall.h"
#include "PlayfieldClasses\\SlingShot.h"
#include "PlayfieldClasses\\Target.h"
#include "PlayfieldClasses\\DropTarget.h"
#include "PlayfieldClasses\\Bumper.h"
#include "PlayfieldClasses\\KickoutHole.h"
#include "PlayfieldClasses\\AccumulatorBall.h"
#include "PlayfieldClasses\\ReturnKickBall.h"
#include "defines.h"
#include "ChangeableStatus.h"

//-------------------------
Playfield::Playfield(MultiplexInputs* multiplexInputs, 
					LatchOutputs* latchOutputsLow, 
					LatchOutputs* LatchOutputsHigh,
					LedControl* ledControl) : Observer(), ChangeableStatus()
//-------------------------
{
	m_muxInputs = multiplexInputs;
	m_LatchOutputLowVoltage = latchOutputsLow;
	m_LatchOutputHighVoltage = LatchOutputsHigh;
	m_LedControl = ledControl;

	m_MotorSR = m_LatchOutputLowVoltage->GetOuput(OUTPUT_MOTOR_SR);
	m_MotorRX = m_LatchOutputLowVoltage->GetOuput(OUTPUT_MOTOR_RX);

	m_LedRamp = m_LatchOutputLowVoltage->GetOuput(OUTPUT_LED_RAMP);

	m_HEADLIGHT_SR = m_LatchOutputLowVoltage->GetOuput(OUTPUT_SR_HEADLIGHT);
	m_HEADLIGHT_RX = m_LatchOutputLowVoltage->GetOuput(OUTPUT_RX_HEADLIGHT);
	m_LockRampOn = m_LatchOutputLowVoltage->GetOuput(OUTPUT_RAMP_LOCK_ON);
	m_LockRampOff = m_LatchOutputLowVoltage->GetOuput(OUTPUT_RAMP_LOCK_OFF);

	m_TurnFlipperOn = m_LatchOutputLowVoltage->GetOuput(OUTPUT_FLIPPER_ON_5V);
	
	m_OutBall = new OutBall(m_muxInputs->GetInput(INPUT_SW_OUTBALL1), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_OUTBALL1_48V),
		m_muxInputs->GetInput(INPUT_SW_OUTBALL2), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_OUTBALL2_48V));

	m_Hole = new KickoutHole(m_muxInputs->GetInput(INPUT_SW_HOLE), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_HOLE_48V));

	m_SlingShotLeft = new SlingShot(m_muxInputs->GetInput(INPUT_SW_SLINGSHOT_LEFT1),
		m_muxInputs->GetInput(INPUT_SW_SLINGSHOT_LEFT2), m_LatchOutputHighVoltage->GetOuput(OUTPUT_SLINGSHOTLEFT_48V));
	
	m_SlingShotRight = new SlingShot(m_muxInputs->GetInput(INPUT_SW_SLINGSHOT_RIGHT1), m_muxInputs->GetInput(INPUT_SW_SLINGSHOT_RIGHT2),
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_SLINGSHOTRIGHT_48V));

	m_TargetOutLaneLeft = new Target(m_muxInputs->GetInput(INPUT_SW_OUTLANE_LEFT), m_LedControl, LED_OUTLANE_LEFT);
	m_TargetReturnBallLeft = new Target(m_muxInputs->GetInput(INPUT_SW_RETURNBALL_LEFT), m_LedControl, LED_RETURNBALL_LEFT);
	m_TargetReturnBallRight = new Target(m_muxInputs->GetInput(INPUT_SW_RETURNBALL_RIGHT), m_LedControl, LED_RETURNBALL_RIGHT);
	m_TargetOutLaneRight = new Target(m_muxInputs->GetInput(INPUT_SW_OUTLANE_RIGHT), m_LedControl, LED_OUTLANE_RIGHT);

	m_TargetGreen1 = new Target(m_muxInputs->GetInput(INPUT_SW_TARGET_GREEN1), m_LedControl, LED_TARGET_GREEN1);
	m_TargetRed1 = new Target(m_muxInputs->GetInput(INPUT_SW_TARGET_RED1), m_LedControl, LED_TARGET_RED1);

	m_DropTarget5 = new DropTarget(m_muxInputs->GetInput(INPUT_SW_DROPTARGET_51),
		m_muxInputs->GetInput(INPUT_SW_DROPTARGET_52), m_muxInputs->GetInput(INPUT_SW_DROPTARGET_53),
		m_muxInputs->GetInput(INPUT_SW_DROPTARGET_54), m_muxInputs->GetInput(INPUT_SW_DROPTARGET_55),
			m_LatchOutputHighVoltage->GetOuput(OUTPUT_DROPTARGET5_48V),m_LedControl);
	m_DropTarget5->AddLeds(LED_DROPTARGET_51, LED_DROPTARGET_52, LED_DROPTARGET_53, LED_DROPTARGET_54, LED_DROPTARGET_55);

	m_DropTarget3 = new DropTarget(m_muxInputs->GetInput(INPUT_SW_DROPTARGET_31),
		m_muxInputs->GetInput(INPUT_SW_DROPTARGET_32), m_muxInputs->GetInput(INPUT_SW_DROPTARGET_33),
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_DROPTARGET3_48V),m_LedControl);
	m_DropTarget3->AddLeds(LED_TARGET_GREEN2, LED_TARGET_YELLOW2, LED_TARGET_RED2);

	m_muxInputs->GetInput(INPUT_SW_LAUNCHBALL)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_ACCJUMP)->AddObserverToEdgePositive(this);

	m_muxInputs->GetInput(INPUT_SW_ROLLOVER_STAR_RED1)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_TARGET_RED2)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_TARGET_YELLOW2)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_TARGET_GREEN2)->AddObserverToEdgePositive(this);

	m_muxInputs->GetInput(INPUT_SW_TARGET_YELLOW1)->AddObserverToEdgePositive(this);

	m_BumperLeft   = new Bumper(m_muxInputs->GetInput(INPUT_SW_BUMPER_LEFT), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_BUMPER_LEFT_48V), 
		m_LatchOutputLowVoltage->GetOuput(OUTPUT_LED_BUMPER_LEFT));
	m_BumperCenter = new Bumper(m_muxInputs->GetInput(INPUT_SW_BUMPER_CENTER), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_BUMPER_CENTER_48V), 
		m_LatchOutputLowVoltage->GetOuput(OUTPUT_LED_BUMPER_CENTER));
	m_BumperRight  = new Bumper(m_muxInputs->GetInput(INPUT_SW_BUMPER_RIGHT), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_BUMPER_RIGHT_48V), 
		m_LatchOutputLowVoltage->GetOuput(OUTPUT_LED_BUMPER_RIGHT));

	m_muxInputs->GetInput(INPUT_SW_ROLLOVER_STAR_GREEN)->AddObserverToEdgePositive(this);

	m_muxInputs->GetInput(INPUT_SW_ROLLOVER_LEFT)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_ROLLOVER_CENTER)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_ROLLOVER_RIGHT)->AddObserverToEdgePositive(this);

	m_muxInputs->GetInput(INPUT_SW_ROLLOVER_STAR_RED2)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_SPINNER)->AddObserverToEdgePositive(this);

	m_muxInputs->GetInput(INPUT_SW_RAMP_IN)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_RAMP_OUT1)->AddObserverToEdgePositive(this);
	m_muxInputs->GetInput(INPUT_SW_RAMP_OUT2)->AddObserverToEdgePositive(this);

	m_ReturnKickBall = new ReturnKickBall(m_muxInputs->GetInput(INPUT_SW_OUTLANE_LEFT), 
		m_LatchOutputHighVoltage->GetOuput(OUTPUT_RETURNBALL_48V), m_LedControl, LED_OUTLANE_LEFT);

	m_AccumulatorBall = new AccumulatorBall(INPUT_SW_ACCBALL1, INPUT_SW_ACCBALL2, INPUT_SW_ACCBALL3, 
		INPUT_SW_ACCBALL4, OUTPUT_ACCBALL_48V, m_muxInputs, m_LatchOutputHighVoltage);

}

//-------------------------
Playfield::~Playfield()
//-------------------------
{
	delete m_OutBall;
	delete m_Hole;
	delete m_SlingShotLeft;
	delete m_SlingShotRight;
	delete m_TargetOutLaneLeft;
	delete m_TargetReturnBallLeft;
	delete m_TargetReturnBallRight;
	delete m_TargetOutLaneRight;
	delete m_TargetGreen1;
	delete m_TargetRed1;
	delete m_DropTarget5;
	delete m_DropTarget3;
	delete m_BumperLeft;
	delete m_BumperCenter;
	delete m_BumperRight;
	delete m_ReturnKickBall;
	delete m_AccumulatorBall;
}

//---------------------------------------------------------------------//
void Playfield::onNotifySubject(EventType event, byte value)
//---------------------------------------------------------------------//
{
	switch (event)
	{
		case EventType::EdgePositive:
			break;

		case EventType::BallKickHole:
			break;

		case EventType::BumperActivated:
			break;

		case EventType::DropTargetComplete:
			break;

		case EventType::HitTarget:
			break;

		case EventType::LostBall:
			break;

		case EventType::SlingShotActivated:
			break;

		default:
			break;

	}
}

//-------------------------------------------------------//
void Playfield::changeStatus(StatusPinballMachine status)
//-------------------------------------------------------//
{
	if (status == StatusPinballMachine::initplaymode)
	{
		m_TurnFlipperOn->TurnOn();
	}
}

