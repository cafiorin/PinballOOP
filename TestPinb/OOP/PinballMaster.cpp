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
#include "Timer.h"
#include "Output.h"
#include "SlingShot.h"
#include "Bumper.h"
#include "KickoutHole.h"
#include "DropTarget.h"
#include "OutBall.h"
#include "Menu.h"
#include "Multiplex.h"

#ifdef ARDUINOLIB
#include <Wire.h>
#include "ht1632pinball.h"

PinballMaster *m_PinballMaster = NULL;

//-----------------------------------------------------------------------//
void receiveMessageFromAnotherArduinoMaster(int howMany)
//-----------------------------------------------------------------------//
{
	m_PinballMaster->receiveMessageFromAnotherArduino(howMany);
}

//-----------------------------------------------------------------------//
void SetupWireToMaster()
//-----------------------------------------------------------------------//
{
	Wire.begin(ADDRESS_MASTER); // join I2C bus using this address
	Wire.onReceive(receiveMessageFromAnotherArduinoMaster); // register event to handle requests
}

#endif // ARDUINOLIB
/*---------------------------------------------------------------------*/


//							C L A S S


#ifdef ARDUINOLIB
/*---------------------------------------------------------------------*/
PinballMaster::PinballMaster() 
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster Constructor");
	#endif

	m_PinballMaster = this;
	SetupWireToMaster();
}

/*---------------------------------------------------------------------*/
void PinballMaster::Setup(SFEMP3Shield *MP3player, HardwareSerial *serial)
/*---------------------------------------------------------------------*/
{
	m_serial = serial;
	m_MP3player = MP3player;

	for (int ch = 0; ch < MAX_INPUTCHANNELS; ch++)
	{
		m_Inputs[ch] = NULL;
	}

	for (int ch = 0; ch < MAX_OUTPUTCHANNELS; ch++)
	{
		m_Outputs[ch] = NULL;
	}

	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Constructor");
	#endif

	Init();
}

#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballMaster::PinballMaster(const char *szName, HardwareSerial *serial) : Pinball(szName, serial)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster Constructor");
	#endif

	for (int ch = 0; ch < MAX_INPUTCHANNELS; ch++)
	{
		m_Inputs[ch] = NULL;
	}

	for (int ch = 0; ch < MAX_OUTPUTCHANNELS; ch++)
	{
		m_Outputs[ch] = NULL;
	}


	Init();
}

#endif

//---------------------------------------------------------------------//
bool PinballMaster::Init()
//---------------------------------------------------------------------//
{
	m_Status = StatusPinball::initializing;
	printText("Pinball", "init", 0);

	m_LedControl = new LedControl(5,this); //TODO: 5 ?
	m_AttractMode = new AttractMode(this);
	m_Menu = new Menu("Menu", this);
	m_TimerToShowPlayers = new Timer(1000,"TimerSP", this, this, TimerType::continuous);
	m_nSecondsTimerToShowPlayers = 5;
	m_Multiplex = new Multiplex(this, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);


	Input *pInputStartButton = new Input("SB", this, INPUT_START_BUTTON, this);
	Input *pInputMenu = new Input("BM", this, INPUT_MENU_BUTTON, this);
	Input *pInputVolumePlus = new Input("VP", this, I40, this);
	Input *pInputVolumeMinus = new Input("VM", this, I41, this);


	//Create all objects to Arduino Master
	Output *pTurnFlipperOn = new Output("TFO", this, Out0, m_Multiplex);

	OutBall *pOutBall = new OutBall("OB", this, I1, Out1, I2, Out2, m_Multiplex);
	SlingShot *pSlingShotLeft = new SlingShot("SLL", this, I3, I37, Out3, m_Multiplex);
	SlingShot *pSlingShotRight = new SlingShot("SLR", this, I4, I38, Out4, m_Multiplex);

	Input *pInputOutLaneLeft = new Input("OLL", this, I5, this);
	Input *pInputReturnBallLeft = new Input("RBL", this, I6, this);
	Input *pInputReturnBallRight = new Input("RBR", this, I7, this);
	Input *pInputOutLaneRight = new Input("OLR", this, I8, this);

	Input *pInputTargetGreen1 = new Input("TG1", this, I9, this);
	Input *pInputTargetRed1 = new Input("TR1", this, I10, this);

	DropTarget *pDropTarget5 = new DropTarget("DT5", this, I11, I12, I13, I14, I15, Out5, m_Multiplex);
	Input *pInputRolloverStarRed1 = new Input("RSR1", this, I16, this);
	DropTarget *pDropTarget3 = new DropTarget("DT3", this, I17, I18, I19, Out6, m_Multiplex);

	Input *pInputTargetRed2 = new Input("TR2", this, I20, this);
	Input *pInputTargetYellow2 = new Input("TY2", this, I21, this);
	Input *pInputTargetGreen2 = new Input("TG2", this, I22, this);

	Input *pInputTargetYellow1 = new Input("TY1", this, I23, this);

	KickoutHole *pHole = new KickoutHole("HOLE", this, I24, Out7, m_Multiplex);
	Bumper *pBumperLeft = new Bumper("BL", this, I25, Out8, m_Multiplex);
	Bumper *pBumperCenter = new Bumper("BC", this, I26, Out9, m_Multiplex);
	Bumper *pBumperRight = new Bumper("BR", this, I27, Out10, m_Multiplex);

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
	
	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		if (!m_PinballObjs[i]->Init())
		{
			printText("Pinball", "error", 0);
		}
	}

	printText("Pinball", "OK", 0);

	delay(200);

	printText("PRESS", "START", 0);

	m_Status = StatusPinball::attractmode;
	m_AttractMode->Init();

	return true;
}

//---------------------------------------------------------------------//
bool PinballMaster::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	if (event == EVENT_EDGEPOSITIVE)
	{
		#ifdef DEBUGMESSAGES
		Debug("PinballMaster::NotifyEvent edge Positive");
		#endif

		if (m_Status == StatusPinball::attractmode)
		{
			//Start Button pressed
			if (valueToSend == INPUT_START_BUTTON)
			{
				m_TimerToShowPlayers->Start();
				m_Status = StatusPinball::getplayers;
				m_nPlayers = 1;
				m_nSecondsTimerToShowPlayers = 5;
				ShowChooseNumberOfPlayers();
			}
			// Menu Button pressed
			else if (valueToSend == INPUT_MENU_BUTTON)
			{
				m_Status = StatusPinball::menusetup;
			}
		}

		else if (m_Status == StatusPinball::getplayers)
		{
			//Start Button pressed
			if (valueToSend == INPUT_START_BUTTON)
			{
				m_Status = StatusPinball::getplayers;
				m_nPlayers++;
				if (m_nPlayers > MAX_PLAYERS)
				{
					m_nPlayers = 1;
				}
				m_nSecondsTimerToShowPlayers = 5;
				ShowChooseNumberOfPlayers();
				m_TimerToShowPlayers->Start();
			}
		}


		return true;
	}
	else if (event == EVENT_DROPTARGETDOWN)
	{
		#ifdef DEBUGMESSAGES
		Debug("PinballMaster::NotifyEvent Droptarget");
		#endif

		return true;
	}
	else if (event == EVENT_TIMEISOVER)
	{
		#ifdef DEBUGMESSAGES
		Debug("PinballMaster::Timer is over");
		#endif

		if (sender == m_TimerToShowPlayers)
		{
			#ifdef DEBUGMESSAGES
			Debug("...Timer is over show players");
			#endif
			m_nSecondsTimerToShowPlayers--;
			ShowChooseNumberOfPlayers();
			if (m_nSecondsTimerToShowPlayers <= 0)
			{
				m_TimerToShowPlayers->Disable();
				StartGame(m_nPlayers);
			}
		}

		return true;
	}

	return false;
}

//---------------------------------------------------------------------//
void PinballMaster::StartGame(int Players)
//---------------------------------------------------------------------//
{
	//TODO:
	m_Status = StatusPinball::playingmode;
	printText("Player 1", "0000", 0);
}


//---------------------------------------------------------------------//
void PinballMaster::ShowChooseNumberOfPlayers()
//---------------------------------------------------------------------//
{
	if (m_Status == StatusPinball::getplayers)
	{
		char szPlayers[10];
		sprintf(szPlayers, "%d  %ds", m_nPlayers, m_nSecondsTimerToShowPlayers);
		printText("Players", szPlayers, 1);
	}
}


/*---------------------------------------------------------------------*/
PinballMaster::~PinballMaster()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster Destructor");
	#endif
}

/*---------------------------------------------------------------------*/
bool PinballMaster::Loop(int value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage("PinballMaster::Loop");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Loop(value);
	}

	switch (m_Status)
	{
		case StatusPinball::attractmode:
		{
			m_AttractMode->Loop();
		}
		break;

		case StatusPinball::getplayers:
		{
		}
		break;
	}

	return true;
}

//-----------------------------------------------------------------------//
void PinballMaster::clearDisplay(int line)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster::clearDisplay");
	#endif


	#ifdef ARDUINOLIB
	char textcol[] = "        ";

	if (line == 0) // Clear All
	{
		textcolor1(0, 1, textcol, RED, 1);
		textcolor1(0, 9, textcol, GREEN, 1);
	}
	else if (line == 1)
	{
		textcolor1(0, 1, textcol, RED, 1);
	}
	else
	{
		textcolor1(0, 9, textcol, GREEN, 1);
	}
	#endif
}

//-----------------------------------------------------------------------//
void PinballMaster::printText(char *text1, char *text2, char font)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::printText");
	#endif

	#ifdef DOS
	int xCursor, yCursor;
	getCursorXY(xCursor, yCursor);

	int x = 70;
	int y = 1;
	clrbox(x, y, x + 10, y + 3, BLACK);
	box(x, y, x + 10, y + 3, y + 6, y + 6, "Display");

	setcolor(RED);
	gotoxy(x + 2, y + 1);
	printf(text1);

	setcolor(GREEN);
	gotoxy(x + 2, y + 2);
	printf(text2);

	gotoxy(xCursor, yCursor);
	#endif


	#ifdef ARDUINOLIB
	clearDisplay(0);
	textcolor1(1, 1, text1, RED, font);
	textcolor1(1, 8 + font, text2, GREEN, font);
	#endif
}

/*---------------------------------------------------------------------*/
void PinballMaster::DataReceived(char c)
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster::DataReceived");
#endif
}
