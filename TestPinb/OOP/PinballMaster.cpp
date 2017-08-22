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
#include "DropTargetWithRemoteInput.h"
#include "OutBall.h"


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

		m_PinballMaster->TurnOnRemoteInput(c);
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

	//Create all objects to Arduino Master
	Output *pTurnFlipperOn = new Output("TFO", this, O0);

	OutBall *pOutBall = new OutBall("OB", this, I1, O1, I2, O2);
	SlingShot *pSlingShotLeft = new SlingShot("SLL", this, I3, I3ALT, O3);
	SlingShot *pSlingShotRight = new SlingShot("SLR", this, I4, I4ALT, O4);

	Input *pInputOutLaneLeft = new Input("OLL", this, I5);
	Input *pInputReturnBallLeft = new Input("RBL", this, I6);
	Input *pInputReturnBallRight = new Input("RBR", this, I7);
	Input *pInputOutLaneRight = new Input("OLR", this, I8);

	Input *pInputTargetGreen1 = new Input("TG1", this, I9);
	Input *pInputTargetRed1 = new Input("TR1", this, I10);

	DropTarget *pDropTarget5 = new DropTarget("DT5", this, I11, I12, I13, I14, I15, O5);
	Input *pInputRolloverStarRed1 = new Input("RSR1", this, I16);
	DropTargetWithRemoteInput *pDropTarget3 = new DropTargetWithRemoteInput("DT3", this, I17, I18, I19, O6);

	Input *pInputTargetRed2 = new Input("TR2", this, I20);
	Input *pInputTargetYellow2 = new Input("TY2", this, I21);
	Input *pInputTargetGreen2 = new Input("TG2", this, I22);

	Input *pInputTargetYellow1 = new Input("TY1", this, I23);

	KickoutHole *pHole = new KickoutHole("HOLE", this, I24, O7);
	Bumper *pBumperLeft = new Bumper("BL", this, I25, O8);
	Bumper *pBumperCenter = new Bumper("BC", this, I26, O9);
	Bumper *pBumperRight = new Bumper("BR", this, I27, O10);

	Input *pInputRolloverStarGreen = new Input("RSG", this, I28);

	Input *pInputRolloverLeft = new Input("RML", this, I29);
	Input *pInputRolloverCenter = new Input("RMC", this, I30);
	Input *pInputRolloverRight = new Input("RMR", this, I31);

	Input *pInputRolloverStarRed2 = new Input("RSR2", this, I32);
	Input *pInputTargetHigher = new Input("TH", this, I33);
	Input *pInputSpinner = new Input("Spin", this, I37);

	//Remote Inputs:
	RemoteInput *pInputRampIn = new RemoteInput("RampIn", this, I34);
	RemoteInput *pInputRampOut1 = new RemoteInput("RampO1", this, I35);
	RemoteInput *pInputRampOut2 = new RemoteInput("RampO2", this, I36);

	RemoteInput *pInputStartButton = new RemoteInput("SB", this, I38);
	RemoteInput *pInputMenu = new RemoteInput("BM", this, I39);
	RemoteInput *pInputVolumePlus = new RemoteInput("VP", this, I40);
	RemoteInput *pInputVolumeMinus = new RemoteInput("VM", this, I41);

}

/*---------------------------------------------------------------------*/
PinballMaster::~PinballMaster()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster Destructor");
	#endif
}

//-----------------------------------------------------------------------//
void PinballMaster::TurnOnRemoteInput(char sw)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster TurnOnRemoteInput");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		if (m_PinballObjs[i]->IsRemoteObject())
		{
			RemoteInput *input = dynamic_cast<RemoteInput *>(m_PinballObjs[i]);
			if (input != NULL)
			{
				if (input->GetPortNumber() == sw)
				{
					input->EmulateInput(true);
				}
			}
		}
	}
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

