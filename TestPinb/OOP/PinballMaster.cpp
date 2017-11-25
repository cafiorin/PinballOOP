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
#include "ReturnKickBall.h"
#include "AccumulatorBall.h"
#include "DropTarget.h"
#include "OutBall.h"
#include "Menu.h"
#include "Multiplex.h"
#include "SelfTest.h"
#include "Stage0.h"
#include "Player.h"
#include "DefinesMp3.h"

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
	m_Status = StatusPinball::initializing;
	m_nBallByPlayer = MAX_BALLS;
	m_enableSfx = true;
	m_PinballMaster = this;
	SetupWireToMaster();

	m_LedControl = NULL;
	m_SelfTest = NULL;
	m_AttractMode = NULL;
	m_Menu = NULL;
	m_TimerToShowPlayers = NULL;
	m_nSecondsTimerToShowPlayers = 5;
	m_Multiplex = NULL;

}

/*---------------------------------------------------------------------*/
void PinballMaster::Setup(SFEMP3Shield *MP3player, HardwareSerial *serial)
/*---------------------------------------------------------------------*/
{
	ht1632_setup();
	m_serial = serial;

	#ifdef DEBUGMESSAGESCREATION
	LogMessage("Pinball Constructor");
	#endif

	m_MP3player = MP3player;

	for (int ch = 0; ch < MAX_INPUTCHANNELS; ch++)
	{
		m_Inputs[ch] = NULL;
	}

	for (int ch = 0; ch < MAX_OUTPUTCHANNELS; ch++)
	{
		m_Outputs[ch] = NULL;
	}

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_Players[i] = new Player(this);
	}

	CreateObjects();
}

#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballMaster::PinballMaster(const char *szName, HardwareSerial *serial) : Pinball(szName, serial)
/*---------------------------------------------------------------------*/
{
	m_Status = StatusPinball::initializing;
	m_nBallByPlayer = MAX_BALLS;
	m_enableSfx = true;

	#ifdef DEBUGMESSAGESCREATION
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

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_Players[i] = new Player(this);
	}

	CreateObjects();
}

#endif

/*---------------------------------------------------------------------*/
PinballMaster::~PinballMaster()
/*---------------------------------------------------------------------*/
{
#ifdef DEBUGMESSAGESCREATION
	LogMessage("PinballMaster Destructor");
#endif
}

//---------------------------------------------------------------------//
//Create all objects to Arduino Master
void PinballMaster::CreateObjects()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("PinballMaster::CreateObjects");
	#endif

	printText("Pinball", "init", 0);

	m_LedControl = new LedControl(this);
	m_Menu = new Menu("Menu", this);
	m_SelfTest = new SelfTest(this);
	m_TimerToShowPlayers = new Timer(1000, "TimerSP", this, this, TimerType::continuous);
	m_nSecondsTimerToShowPlayers = 5;
	m_Multiplex = new Multiplex(this, 23, 25, 27, 29, 22, 24, 26, 28, 30, 31, 32);

	Input *pInputStartButton = new Input("SB", this, INPUT_START_BUTTON, this);
	Input *pInputMenu = new Input("BM", this, INPUT_MENU_BUTTON, this);
	Input *pInputVolumePlus = new Input("VP", this, INPUT_UP_BUTTON, this);
	Input *pInputVolumeMinus = new Input("VM", this, INPUT_DOWN_BUTTON, this);

	m_TurnFlipperOn = new Output("TFO", this, OUTPUT_FLIPPER_ON_5V, m_Multiplex);
	m_OutBall = new OutBall("OB", this, INPUT_SW_OUTBALL1, OUTPUT_OUTBALL1_48V, INPUT_SW_OUTBALL1, OUTPUT_OUTBALL2_48V, m_Multiplex);
	m_Hole = new KickoutHole("HOLE", this, INPUT_SW_HOLE, OUTPUT_HOLE_48V, m_Multiplex);

	SlingShot *pSlingShotLeft = new SlingShot("SLL", this, INPUT_SW_SLINGSHOT_LEFT1, INPUT_SW_SLINGSHOT_LEFT2, OUTPUT_SLINGSHOTLEFT_48V, m_Multiplex);
	SlingShot *pSlingShotRight = new SlingShot("SLR", this, INPUT_SW_SLINGSHOT_RIGHT1, INPUT_SW_SLINGSHOT_RIGHT2, OUTPUT_SLINGSHOTRIGHT_48V, m_Multiplex);

	Input *pInputOutLaneLeft = new Input("OLL", this, INPUT_SW_OUTLANE_LEFT, this);
	Input *pInputReturnBallLeft = new Input("RBL", this, INPUT_SW_RETURNBALL_LEFT, this);
	Input *pInputReturnBallRight = new Input("RBR", this, INPUT_SW_RETURNBALL_RIGHT, this);
	Input *pInputOutLaneRight = new Input("OLR", this, INPUT_SW_OUTLANE_RIGHT, this);

	Input *pInputTargetGreen1 = new Input("TG1", this, INPUT_SW_TARGET_GREEN1, this);
	Input *pInputTargetRed1 = new Input("TR1", this, INPUT_SW_TARGET_RED1, this);

	DropTarget *pDropTarget5 = new DropTarget("DT5", this, INPUT_SW_DROPTARGET_51, INPUT_SW_DROPTARGET_52, INPUT_SW_DROPTARGET_53, INPUT_SW_DROPTARGET_54, INPUT_SW_DROPTARGET_55, OUTPUT_DROPTARGET5_48V, m_Multiplex);
	Input *pInputRolloverStarRed1 = new Input("RSR1", this, INPUT_SW_ROLLOVER_STAR_RED1, this);
	DropTarget *pDropTarget3 = new DropTarget("DT3", this, INPUT_SW_DROPTARGET_31, INPUT_SW_DROPTARGET_32, INPUT_SW_DROPTARGET_33, OUTPUT_DROPTARGET3_48V, m_Multiplex);

	Input *pInputTargetRed2 = new Input("TR2", this, INPUT_SW_TARGET_RED2, this);
	Input *pInputTargetYellow2 = new Input("TY2", this, INPUT_SW_TARGET_YELLOW2, this);
	Input *pInputTargetGreen2 = new Input("TG2", this, INPUT_SW_TARGET_GREEN2, this);

	Input *pInputTargetYellow1 = new Input("TY1", this, INPUT_SW_TARGET_YELLOW1, this);

	Bumper *pBumperLeft = new Bumper("BL", this, INPUT_SW_BUMPER_LEFT, OUTPUT_BUMPER_LEFT_48V, m_Multiplex);
	Bumper *pBumperCenter = new Bumper("BC", this, INPUT_SW_BUMPER_CENTER, OUTPUT_BUMPER_CENTER_48V, m_Multiplex);
	Bumper *pBumperRight = new Bumper("BR", this, INPUT_SW_BUMPER_RIGHT, OUTPUT_BUMPER_RIGHT_48V, m_Multiplex);

	Input *pInputRolloverStarGreen = new Input("RSG", this, INPUT_SW_ROLLOVER_STAR_GREEN, this);

	Input *pInputRolloverLeft = new Input("RML", this, INPUT_SW_ROLLOVER_LEFT, this);
	Input *pInputRolloverCenter = new Input("RMC", this, INPUT_SW_ROLLOVER_CENTER, this);
	Input *pInputRolloverRight = new Input("RMR", this, INPUT_SW_ROLLOVER_RIGHT, this);

	Input *pInputRolloverStarRed2 = new Input("RSR2", this, INPUT_SW_ROLLOVER_STAR_RED2, this);
	Input *pInputTargetHigher = new Input("TH", this, INPUT_SW_TARGET_HIGHER, this);
	Input *pInputSpinner = new Input("Spin", this, INPUT_SW_SPINNER, this);

	Input *pInputRampIn = new Input("RampIn", this, INPUT_SW_RAMP_IN, this);
	Input *pInputRampOut1 = new Input("RampO1", this, INPUT_SW_RAMP_OUT1, this);
	Input *pInputRampOut2 = new Input("RampO2", this, INPUT_SW_RAMP_OUT2, this);

	ReturnKickBall *returnKB = new ReturnKickBall("RKB", this, INPUT_SW_RETURNBALL_LEFT, OUTPUT_RETURNBALL_48V, m_Multiplex);
	AccumulatorBall *accBall = new AccumulatorBall("RKB", this, INPUT_SW_ACCBALL1, INPUT_SW_ACCBALL2, INPUT_SW_ACCBALL3, INPUT_SW_ACCBALL4, OUTPUT_ACCBALL_48V, m_Multiplex);

	CreateStages();

	//Last 
	m_AttractMode = new AttractMode(this);

	printText("Pinball", "OK", 0);
	delay(200);

	Init();
}

//---------------------------------------------------------------------//
void PinballMaster::CreateStages()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::CreateStages");
	#endif

	m_TotalStages = 1;

	//TODO:Stages
	m_Stages[0] = new Stage0(this,0);
}

//---------------------------------------------------------------------//
bool PinballMaster::Init()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::Init");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		PinballObject *pObject = m_PinballObjs[i];
		if (!pObject->Init())
		{
			#ifdef DEBUGMESSAGES
			LogMessage("Pinball Error");
			delay(500);
			#endif
		}
	}

	m_Status = StatusPinball::attractmode;

	return true;
}

//---------------------------------------------------------------------//
bool PinballMaster::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessageValue("PinballMaster::NotifyEvent",event);
	#endif

	if (event >= EVENT_TEST_INIT && event <= EVENT_TEST_FINISH)
	{
		#ifdef DEBUGMESSAGES
		Debug("PinballMaster::NotifyEvent Test");
		#endif

		return SetupTest(event);
	}
	else if (event == EVENT_EDGEPOSITIVE)
	{
		#ifdef DEBUGMESSAGES
		Debug("PinballMaster::NotifyEvent edge Positive");
		#endif

		// -- E D G E  P O S I T I V E --
		switch(valueToSend)
		{
		case INPUT_START_BUTTON:
			{
				return EventStartButton(sender);
			}
			break;

		case INPUT_MENU_BUTTON:
			{
				return EventMenuButton(sender);
			}
			break;

		case INPUT_UP_BUTTON:
			{
				return EventUpDownButton(sender,true);
			}
			break;

		case INPUT_DOWN_BUTTON:
			{
				return EventUpDownButton(sender,false);
			}
			break;
		}

		// -- P L A Y F I E L D --
		if (valueToSend >= INPUT_PLAYFIELD_INIT && valueToSend <= INPUT_PLAYFIELD_FINISH)
		{
			return PlayfieldEvent(sender, event, valueToSend);
		}

		return true;
	}
	// -- D R O P  T A R G E T --
	else if (event == EVENT_DROPTARGETDOWN)
	{
		return PlayfieldEvent(sender, event, valueToSend);
	}
	// -- T I M E R  I S  O V E R --
	else if (event == EVENT_TIMEISOVER)
	{
		return TimerIsOver(sender);
	}
	else if (event == EVENT_LOST_BALL)
	{
		PlayerLostBall();
	}

	return false;
}

//Start Button pressed
//---------------------------------------------------------------------//
bool PinballMaster::EventStartButton(PinballObject *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::EventStartButton");
	#endif

	if (m_Status == StatusPinball::attractmode)
	{
		m_TimerToShowPlayers->Start();
		m_Status = StatusPinball::getplayers;
		m_nPlayers = 1;
		m_nSecondsTimerToShowPlayers = 5;
		ShowChooseNumberOfPlayers();
		return true;
	}
	else if (m_Status == StatusPinball::getplayers)
	{
		m_nPlayers++;
		if (m_nPlayers > MAX_PLAYERS)
		{
			m_nPlayers = 1;
		}
		m_nSecondsTimerToShowPlayers = 5;
		ShowChooseNumberOfPlayers();
		m_TimerToShowPlayers->Start();
		return true;
	}
	return false;
}

//Menu Button pressed
//---------------------------------------------------------------------//
bool PinballMaster::EventMenuButton(PinballObject *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::EventMenuButton");
	#endif


	if (m_Status == StatusPinball::attractmode || m_Status == StatusPinball::menusetup)
	{
		m_Status = StatusPinball::menusetup;
		m_Menu->PressButtonMenu();
		return true;
	}
	else if (m_Status == StatusPinball::menutest)
	{
		SetupTest(EVENT_TEST_EXIT_MENU);
	}

	return false;
}

//---------------------------------------------------------------------//
bool PinballMaster::EventUpDownButton(PinballObject *sender, bool upButton)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::EventUpDownButton");
	#endif

	if (m_Status == StatusPinball::menusetup)
	{
		m_Menu->PressUpDownButton(upButton);
		return true;
	}
	else if (m_Status == StatusPinball::menutest)
	{
		m_SelfTest->EventUpDownButton(sender, upButton);
	}

	return false;
}

//---------------------------------------------------------------------//
bool PinballMaster::PlayfieldEvent(PinballObject *sender, int event, int valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::PlayfieldEvent");
	#endif

	if (m_Status == StatusPinball::playingmode)
	{
		m_Players[m_playerPlaying]->NotifyEvent(sender, event, valueToSend);
	}

	return true;
}

//---------------------------------------------------------------------//
bool PinballMaster::TimerIsOver(PinballObject *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::TimerIsOver");
	#endif

	if (sender == m_TimerToShowPlayers)
	{
		m_nSecondsTimerToShowPlayers--;
		ShowChooseNumberOfPlayers();
		if (m_nSecondsTimerToShowPlayers <= 0)
		{
			m_TimerToShowPlayers->Disable();
			StartGame(m_nPlayers);
		}
		return true;
	}

	return false;
}

//---------------------------------------------------------------------//
bool PinballMaster::SetupTest(int event)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::SetupTest");
	#endif

	if (event == EVENT_TEST_EXIT_MENU)
	{
		m_SelfTest->FinishTest();
		m_Status = StatusPinball::attractmode;
		m_AttractMode->Init();
	}
	else if (event >= EVENT_TEST_INIT && event <= EVENT_TEST_FINISH)
	{
		if (event == EVENT_TEST_NBALLS3 || event == EVENT_TEST_NBALLS4 || event == EVENT_TEST_NBALLS5)
		{
			this->SetBallsByPlayer(3 + (event - EVENT_TEST_NBALLS3));
			printText("Set", "Ball", 1);
			delay(300);
			m_Status = StatusPinball::attractmode;
			m_AttractMode->Init();
			return true;
		}
		else
		{
			m_Status = StatusPinball::menutest;
			m_SelfTest->StartTest(event);
		}
	}

	return true;
}

//---------------------------------------------------------------------//
void PinballMaster::StartGame(int Players)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::StartGame");
	#endif

	m_nPlayers = Players;

	m_Status = StatusPinball::playingmode;

	for (int i = 0; i < m_nPlayers; i++)
	{
		m_Players[i]->Init();
	}

	m_playerPlaying = 0;
	m_Players[m_playerPlaying]->SetCurrentPlayer(m_playerPlaying);
	m_TurnFlipperOn->TurnOn();
}

//---------------------------------------------------------------------//
void PinballMaster::PlayerLostBall()
//---------------------------------------------------------------------//
{
	if (m_Status == StatusPinball::playingmode)
	{
		if (!m_OutBall->IsThereAnyBallInGame())
		{
			m_TurnFlipperOn->TurnOff();

			m_Players[m_playerPlaying]->LostBall();
			NextPlayer();
		}
		else
		{
			//Ball in hole ?
			if (m_Hole->IsThereBall())
			{
				m_Hole->LanchBall();
			}
		}

	}
}

//---------------------------------------------------------------------//
void PinballMaster::NextPlayer()
//---------------------------------------------------------------------//
{
	m_playerPlaying++;
	if (m_playerPlaying >= m_nPlayers)
		m_playerPlaying = 0;

	bool isAnyPlayerWaiting = false;
	int player = m_playerPlaying;
	do
	{
		player++;
	
		if (player >= m_nPlayers)
			player = 0;

		if (m_Players[player]->GetStatus() == StatusPlayer::waiting)
		{
			isAnyPlayerWaiting = true;
			m_playerPlaying = player;
			break;
		}
	} while(player == m_playerPlaying);

	if (isAnyPlayerWaiting)
	{
		if (m_Players[m_playerPlaying]->SetCurrentPlayer(m_playerPlaying))
		{
			m_TurnFlipperOn->TurnOn();
		}
	}
	else
	{
		//GameOver
		m_Status = StatusPinball::attractmode;
		m_AttractMode->InitGameOver();
	}
}


//---------------------------------------------------------------------//
void PinballMaster::GetNewBall()
//---------------------------------------------------------------------//
{
	if (m_Status == StatusPinball::playingmode)
	{
		m_OutBall->LanchBall();
	}
}

//---------------------------------------------------------------------//
void PinballMaster::ShowChooseNumberOfPlayers()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("PinballMaster::ShowChooseNumberOfPlayers");
	#endif

	if (m_Status == StatusPinball::getplayers)
	{
		char szPlayers[10];
		sprintf(szPlayers, "%d  %ds", m_nPlayers, m_nSecondsTimerToShowPlayers);
		printText("Players", szPlayers, 0);
	}
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
			m_LedControl->AttractModeLoop();
		}
		break;

		case StatusPinball::playingmode:
		{
			m_Players[m_playerPlaying]->Loop(0);
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

//---------------------------------------------------------------------//
void PinballMaster::DataReceived(char c)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage("PinballMaster::DataReceived");
	#endif
}

//---------------------------------------------------------------------//
void PinballMaster::PlaySongToInput(int portNumber)
//---------------------------------------------------------------------//
{
	if(m_Status == StatusPinball::playingmode)
	{
		switch (portNumber)
		{
		case INPUT_SW_OUTBALL1:
			playSong(MP3_OUTBALL);
			break;
		//case INPUT_SW_OUTBALL2:

		case INPUT_SW_SLINGSHOT_LEFT1:
		case INPUT_SW_SLINGSHOT_LEFT2:
			playSong(MP3_SLINGSHOT_LEFT);
			break;

		case INPUT_SW_SLINGSHOT_RIGHT1:
		case INPUT_SW_SLINGSHOT_RIGHT2:
			playSong(MP3_SLINGSHOT_RIGHT);
			break;

		case INPUT_SW_BUMPER_CENTER:
			playSong(MP3_BUMPER_CENTER);
			break;

		case INPUT_SW_BUMPER_LEFT:
			playSong(MP3_BUMPER_LEFT);
			break;

		case INPUT_SW_BUMPER_RIGHT:
			playSong(MP3_BUMPER_RIGHT);
			break;

		case INPUT_SW_LAUNCHBALL:
			playSong(MP3_LAUNCHBALL);
			break;

		case INPUT_SW_OUTLANE_LEFT:
			playSong(MP3_OUTLANE_LEFT);
			break;

		case INPUT_SW_OUTLANE_RIGHT:
			playSong(MP3_OUTLANE_RIGHT);
			break;

		case INPUT_SW_RETURNBALL_LEFT:
			playSong(MP3_RETURNBALL_LEFT);
			break;

		case INPUT_SW_RETURNBALL_RIGHT:
			playSong(MP3_RETURNBALL_RIGHT);
			break;

		case INPUT_SW_TARGET_RED1:
			playSong(MP3_TARGET_RED1);
			break;

		case INPUT_SW_TARGET_GREEN1:
			playSong(MP3_TARGET_GREEN1);
			break;

		case INPUT_SW_TARGET_YELLOW1:
			playSong(MP3_TARGET_YELLOW1);
			break;

		case INPUT_SW_TARGET_RED2:
			playSong(MP3_TARGET_RED2);
			break;

		case INPUT_SW_TARGET_GREEN2:
			playSong(MP3_TARGET_GREEN2);
			break;

		case INPUT_SW_TARGET_YELLOW2:
			playSong(MP3_TARGET_YELLOW2);
			break;

		case INPUT_SW_DROPTARGET_51:
			playSong(MP3_DROPTARGET_51);
			break;

		case INPUT_SW_DROPTARGET_52:
			playSong(MP3_DROPTARGET_52);
			break;

		case INPUT_SW_DROPTARGET_53:
			playSong(MP3_DROPTARGET_53);
			break;

		case INPUT_SW_DROPTARGET_54:
			playSong(MP3_DROPTARGET_54);
			break;

		case INPUT_SW_DROPTARGET_55:
			playSong(MP3_DROPTARGET_55);
			break;

		case INPUT_SW_DROPTARGET_31:
			playSong(MP3_DROPTARGET_31);
			break;

		case INPUT_SW_DROPTARGET_32:
			playSong(MP3_DROPTARGET_32);
			break;

		case INPUT_SW_DROPTARGET_33:
			playSong(MP3_DROPTARGET_33);
			break;

		case INPUT_SW_ROLLOVER_STAR_GREEN:
			playSong(MP3_ROLLOVER_STAR_GREEN);
			break;

		case INPUT_SW_ROLLOVER_STAR_RED1:
			playSong(MP3_ROLLOVER_STAR_RED1);
			break;

		case INPUT_SW_ROLLOVER_STAR_RED2:
			playSong(MP3_ROLLOVER_STAR_RED2);
			break;

		case INPUT_SW_ROLLOVER_LEFT:
			playSong(MP3_ROLLOVER_LEFT);
			break;

		case INPUT_SW_ROLLOVER_CENTER:
			playSong(MP3_ROLLOVER_CENTER);
			break;

		case INPUT_SW_ROLLOVER_RIGHT:
			playSong(MP3_ROLLOVER_RIGHT);
			break;

		case INPUT_SW_TARGET_HIGHER:
			playSong(MP3_TARGET_HIGHER);
			break;

		case INPUT_SW_RAMP_IN:
			playSong(MP3_RAMP_IN);
			break;

		case INPUT_SW_RAMP_OUT1:
			playSong(MP3_RAMP_OUT1);
			break;

		case INPUT_SW_RAMP_OUT2:
			playSong(MP3_RAMP_OUT2);
			break;

		case INPUT_SW_SPINNER:
			playSong(MP3_SPINNER);
			break;

		case INPUT_SW_HOLE:
			playSong(MP3_HOLE);
			break;

		case INPUT_SW_ACCBALL1:
			playSong(MP3_ACCBALL1);
			break;

		case INPUT_SW_ACCBALL2:
			playSong(MP3_ACCBALL2);
			break;

		case INPUT_SW_ACCBALL3:
			playSong(MP3_ACCBALL3);
			break;

		case INPUT_SW_ACCBALL4:
			playSong(MP3_ACCBALL4);
			break;

		default:
			playSong(MP3_STARTBUTTONPORT);
			break;
		}
	}
	else
	{
		switch (portNumber)
		{
		case INPUT_MENU_BUTTON:
			playSong(MP3_MENU_BUTTON);
			break;
		case INPUT_UP_BUTTON:
			playSong(MP3_UP_BUTTON);
			break;
		case INPUT_DOWN_BUTTON:
			playSong(MP3_DOWN_BUTTON);
			break;
		}
	}
}

