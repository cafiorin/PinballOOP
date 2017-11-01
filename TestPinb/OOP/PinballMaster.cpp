/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "PinballMaster.h"
#include "Pinball.h"
#include "PinballObject.h"
#include "HardwareSerial.h"
#include "Vector.h"
#include "Utils.h"

#include "Input.h"
#include "Output.h"
#include "SlingShot.h"
#include "Bumper.h"
#include "KickoutHole.h"
#include "DropTarget.h"
#include "OutBall.h"
#include "Menu.h"
#include "Multiplex.h"

#ifdef ARDUINO
#include <Wire.h>

const int address_master = 4;  // the address to be used by the communicating devices
PinballMaster *m_PinballMaster = NULL;

//-----------------------------------------------------------------------//
void receiveMessageFromAnotherArduino(int howMany)
//-----------------------------------------------------------------------//
{
	while (Wire.available() > 0)
	{
		char c = Wire.read(); // receive byte as a character

		char msg[6];
		sprintf(msg, "%d", c);
		char sw[] = "SW";
		m_PinballMaster->printText(sw, msg, 1);
	}
}

//-----------------------------------------------------------------------//
void SetupWire()
//-----------------------------------------------------------------------//
{
	Wire.begin(address_master); // join I2C bus using this address
	Wire.onReceive(receiveMessageFromAnotherArduino); // register event to handle requests
}

//-----------------------------------------------------------------------//
void sendMessageToAnotherArduinoGlobal(char c)
//-----------------------------------------------------------------------//
{
	// send the data
	Wire.beginTransmission(5); // transmit to device
	Wire.write(c);
	Wire.endTransmission();
}

#endif // ARDUINO
/*---------------------------------------------------------------------*/


//							C L A S S


/*---------------------------------------------------------------------*/
#ifdef ARDUINO
PinballMaster::PinballMaster(const char *szName, SFEMP3Shield *MP3player, HardwareSerial *serial, bool master = false) : Pinball(szName, serial, true)
#endif

#ifdef DOS
PinballMaster::PinballMaster(const char *szName, HardwareSerial *serial) : Pinball(szName, serial, true)
#endif
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster Constructor");
	#endif

	#ifdef ARDUINO
	m_PinballMaster = this;
	SetupWire();
	#endif

	m_Menu = new Menu("Menu", this);

	m_Multiplex = new Multiplex(22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

	//Create all objects to Arduino Master
	Output *pTurnFlipperOn = new Output("TFO", this, O0);

	OutBall *pOutBall = new OutBall("OB", this, I1, O1, I2, O2);
	SlingShot *pSlingShotLeft = new SlingShot("SLL", this, I3, I3ALT, O3);
	SlingShot *pSlingShotRight = new SlingShot("SLR", this, I4, I4ALT, O4);

	Input *pInputOutLaneLeft = new Input("OLL", this, I5,this);
	Input *pInputReturnBallLeft = new Input("RBL", this, I6, this);
	Input *pInputReturnBallRight = new Input("RBR", this, I7, this);
	Input *pInputOutLaneRight = new Input("OLR", this, I8, this);

	Input *pInputTargetGreen1 = new Input("TG1", this, I9, this);
	Input *pInputTargetRed1 = new Input("TR1", this, I10, this);

	DropTarget *pDropTarget5 = new DropTarget("DT5", this, I11, I12, I13, I14, I15, O5);
	Input *pInputRolloverStarRed1 = new Input("RSR1", this, I16, this);
	//DropTargetWithRemoteInput *pDropTarget3 = new DropTargetWithRemoteInput("DT3", this, I17, I18, I19, O6);

	Input *pInputTargetRed2 = new Input("TR2", this, I20, this);
	Input *pInputTargetYellow2 = new Input("TY2", this, I21, this);
	Input *pInputTargetGreen2 = new Input("TG2", this, I22, this);

	Input *pInputTargetYellow1 = new Input("TY1", this, I23, this);

	KickoutHole *pHole = new KickoutHole("HOLE", this, I24, O7);
	Bumper *pBumperLeft = new Bumper("BL", this, I25, O8);
	Bumper *pBumperCenter = new Bumper("BC", this, I26, O9);
	Bumper *pBumperRight = new Bumper("BR", this, I27, O10);

	Input *pInputRolloverStarGreen = new Input("RSG", this, I28, this);

	Input *pInputRolloverLeft = new Input("RML", this, I29, this);
	Input *pInputRolloverCenter = new Input("RMC", this, I30, this);
	Input *pInputRolloverRight = new Input("RMR", this, I31, this);

	Input *pInputRolloverStarRed2 = new Input("RSR2", this, I32, this);
	Input *pInputTargetHigher = new Input("TH", this, I33, this);
	Input *pInputSpinner = new Input("Spin", this, I37, this);

	Input *pInputRampIn = new Input("RampIn", this, I34, this);
	Input *pInputRampOut1 = new Input("RampO1", this, I35, this);
	Input *pInputRampOut2 = new Input("RampO2", this, I36, this);

	Input *pInputStartButton = new Input("SB", this, I38, this);
	Input *pInputMenu = new Input("BM", this, I39, this);
	Input *pInputVolumePlus = new Input("VP", this, I40, this);
	Input *pInputVolumeMinus = new Input("VM", this, I41, this);
}

//---------------------------------------------------------------------//
bool PinballMaster::NotifyEvent(int id, int event)
//---------------------------------------------------------------------//
{
	if (event == EVENT_EDGEPOSITIVE)
	{
		return true;
	}
	return false;
}

/*---------------------------------------------------------------------*/
PinballMaster::~PinballMaster()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster Destructor");
	#endif
}

void PinballMaster::sendMessageToAnotherArduino(char msg)
{
	#ifdef ARDUINO
	sendMessageToAnotherArduinoGlobal(msg);
	#endif // ARDUINO

	#ifdef DOS

	#endif

}

char PinballMaster::receiveMessageFromAnotherArduino()
{
	return 0;
}

