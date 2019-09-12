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
#include "InputArduino.h"
//#include "OutputArduino.h"
#include "Timer.h"
#include "Output.h"
#include "SlingShot.h"
#include "Bumper.h"
#include "KickoutHole.h"
#include "ReturnKickBall.h"
#include "AccumulatorBall.h"
#include "DropTarget.h"
#include "Target.h"
#include "OutBall.h"
#include "Menu.h"
#include "Multiplex.h"
#include "DefinesMp3.h"
#include "LedControl.h"

#ifdef ARDUINOLIB
#include <Wire.h>
#include "ht1632pinball.h"

/*---------------------------------------------------------------------*/
PinballMaster::PinballMaster()
/*---------------------------------------------------------------------*/
{
}

/*---------------------------------------------------------------------*/
void PinballMaster::Setup(SFEMP3Shield *MP3player, HardwareSerial *serial)
/*---------------------------------------------------------------------*/
{
	m_Serial = serial;
	m_Pinball = this;

	ht1632_setup();

	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("Pinball Setup"));
	#endif

	m_MP3player = MP3player;

	InitVars();
	CreateObjects();
}

#endif

#ifdef DOS
/*---------------------------------------------------------------------*/
PinballMaster::PinballMaster(HardwareSerial *serial) : Pinball()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballMaster Construtor"));
	#endif

	this->m_Pinball = this;
	this->m_Serial = serial;

	InitVars();
	CreateObjects();
}

#endif

/*---------------------------------------------------------------------*/
PinballMaster::~PinballMaster()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballMaster Destructor"));
	#endif

	for (uint8_t i = m_PinballObjs.size()-1; i >=0 ; i--)
	{
		delete m_PinballObjs[i];
	}
}

//---------------------------------------------------------------------//
void PinballMaster::InitVars()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballMaster::InitVars"));
	#endif

	printText("Pinball", "init", 0);

	m_Status = StatusPinball::initializing;
	m_nBallByPlayer = MAX_BALLS;
	m_enableSfx = true;
	m_nSecondsTimerToShowPlayers = 5;

	m_Menu = NULL;
	m_TimerToShowPlayers = NULL;
	m_OutBall = NULL;
	m_Hole = NULL;
	m_TurnFlipperOn = NULL;
	m_DropTarget5 = NULL;
	m_DropTarget3 = NULL;
}


//---------------------------------------------------------------------//
//Create all objects to Arduino Master
void PinballMaster::CreateObjects()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballMaster::CreateObjects"));
	#endif

	m_Multiplex = new Multiplex(/*S0*/23, /*S1*/25, /*S2*/27,/*S3*/29, /*SIn0*/22, /*SIn1*/34, /*SIn2*/36, 
		/*SOut0*/24, A8, A9, A10, A11,
		/*SOut1*/41, A12, A13, A14, A15);
	m_LedControl = new LedControl();

	m_TimerToShowPlayers = new Timer(1000, NULL, TimerType::continuous);

	m_MenuButton = new InputArduino(INPUT_MENU_BUTTON);
	m_UpButton = new InputArduino(INPUT_UP_BUTTON);
	m_DownButton = new InputArduino(INPUT_DOWN_BUTTON);
	m_EnterButton = new InputArduino(INPUT_ENTER_BUTTON);
	m_StartButton = new InputArduino(INPUT_START_BUTTON);

	m_MotorSR = new Output(OUTPUT_MOTOR_SR);
	m_MotorRX = new Output(OUTPUT_MOTOR_RX);

	m_LedRamp = new Output(OUTPUT_LED_RAMP);

	m_HEADLIGHT_SR = new Output(OUTPUT_SR_HEADLIGHT);
	m_HEADLIGHT_RX = new Output(OUTPUT_RX_HEADLIGHT);
	m_LockRampOn   =  new Output(OUTPUT_RAMP_LOCK_ON);
	m_LockRampOff  = new Output(OUTPUT_RAMP_LOCK_OFF);

	m_TurnFlipperOn = new Output(OUTPUT_FLIPPER_ON_5V);
	m_OutBall = new OutBall(INPUT_SW_OUTBALL1, OUTPUT_OUTBALL1_48V, INPUT_SW_OUTBALL2, OUTPUT_OUTBALL2_48V);
	m_Hole = new KickoutHole(INPUT_SW_HOLE, OUTPUT_HOLE_48V);

	new SlingShot(INPUT_SW_SLINGSHOT_LEFT1, INPUT_SW_SLINGSHOT_LEFT2, OUTPUT_SLINGSHOTLEFT_48V);
	new SlingShot(INPUT_SW_SLINGSHOT_RIGHT1, INPUT_SW_SLINGSHOT_RIGHT2, OUTPUT_SLINGSHOTRIGHT_48V);

	new Target(INPUT_SW_OUTLANE_LEFT,LED_OUTLANE_LEFT);
	new Target(INPUT_SW_RETURNBALL_LEFT,LED_RETURNBALL_LEFT);
	new Target(INPUT_SW_RETURNBALL_RIGHT,LED_RETURNBALL_RIGHT);
	new Target(INPUT_SW_OUTLANE_RIGHT,LED_OUTLANE_RIGHT);

	new Target(INPUT_SW_TARGET_GREEN1,LED_TARGET_GREEN1);
	new Target(INPUT_SW_TARGET_RED1, LED_TARGET_RED1);

	m_DropTarget5 = new DropTarget(INPUT_SW_DROPTARGET_51, INPUT_SW_DROPTARGET_52, INPUT_SW_DROPTARGET_53, INPUT_SW_DROPTARGET_54, INPUT_SW_DROPTARGET_55, OUTPUT_DROPTARGET5_48V);
	m_DropTarget5->AddLeds(LED_DROPTARGET_51, LED_DROPTARGET_52, LED_DROPTARGET_53, LED_DROPTARGET_54, LED_DROPTARGET_55);

	m_DropTarget3 = new DropTarget(INPUT_SW_DROPTARGET_31, INPUT_SW_DROPTARGET_32, INPUT_SW_DROPTARGET_33, OUTPUT_DROPTARGET3_48V);
	m_DropTarget3->AddLeds(LED_TARGET_GREEN2, LED_TARGET_YELLOW2, LED_TARGET_RED2);

	new Input(INPUT_SW_ROLLOVER_STAR_RED1);
	new Input(INPUT_SW_TARGET_RED2);
	new Input(INPUT_SW_TARGET_YELLOW2);
	new Input(INPUT_SW_TARGET_GREEN2);

	new Input(INPUT_SW_TARGET_YELLOW1);

	new Bumper(INPUT_SW_BUMPER_LEFT, OUTPUT_BUMPER_LEFT_48V, OUTPUT_LED_BUMPER_LEFT);
	new Bumper(INPUT_SW_BUMPER_CENTER, OUTPUT_BUMPER_CENTER_48V, OUTPUT_LED_BUMPER_CENTER);
	new Bumper(INPUT_SW_BUMPER_RIGHT, OUTPUT_BUMPER_RIGHT_48V, OUTPUT_LED_BUMPER_RIGHT);

	new Input(INPUT_SW_ROLLOVER_STAR_GREEN);

	new Input(INPUT_SW_ROLLOVER_LEFT);
	new Input(INPUT_SW_ROLLOVER_CENTER);
	new Input(INPUT_SW_ROLLOVER_RIGHT);

	new Input(INPUT_SW_ROLLOVER_STAR_RED2);
	new Input(INPUT_SW_SPINNER);

	new Input(INPUT_SW_RAMP_IN);
	new Input(INPUT_SW_RAMP_OUT1);
	new Input(INPUT_SW_RAMP_OUT2);

	new ReturnKickBall(INPUT_SW_OUTLANE_LEFT, OUTPUT_RETURNBALL_48V, LED_OUTLANE_LEFT);
	new AccumulatorBall(INPUT_SW_ACCBALL1, INPUT_SW_ACCBALL2, INPUT_SW_ACCBALL3, INPUT_SW_ACCBALL4, OUTPUT_ACCBALL_48V);

	Init(StatusPinball::initializing);

	printText("Pinball", "OK", 0);
	delay(200);

	Init(StatusPinball::attractmode);
}

//---------------------------------------------------------------------//
bool PinballMaster::Init(StatusPinball status)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::Init"));
	#endif

	m_Status = status;

	size_t size = m_PinballObjs.size();
	for (uint8_t i = 0; i < size ; i++)
	{
		PinballObject *pObject = m_PinballObjs[i];
	//	cout << pObject->getName() << "  ";
		if (!pObject->Init())
		{
			#ifdef DEBUGMESSAGES
			LogMessage(F("Pinball Error"));
			delay(500);
			#endif
		}
	}
	return true;
}

//---------------------------------------------------------------------//
bool PinballMaster::NotifyEvent(Object *sender, uint8_t event, uint8_t valueToSend)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::NotifyEvent"));
	#endif

	if (event >= EVENT_TEST_INIT && event <= EVENT_TEST_FINISH)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("PinballMaster::NotifyEvent Test"));
		#endif

		return SetupTest(event);
	}
	else if (event == EVENT_EDGEPOSITIVE)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("PinballMaster::NotifyEvent edge Positive"));
		#endif

		// -- E D G E  P O S I T I V E --
		switch (valueToSend)
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
			return EventUpDownButton(sender, true);
		}
		break;

		case INPUT_DOWN_BUTTON:
		{
			return EventUpDownButton(sender, false);
		}
		break;
		case INPUT_ENTER_BUTTON:
		{
			return EventEnterButton(sender);
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
		return PlayfieldEvent(sender, event,valueToSend);
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
bool PinballMaster::EventStartButton(Object *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::EventStartButton"));
	#endif

	if (m_Status == StatusPinball::attractmode)
	{
		if (m_TimerToShowPlayers != NULL)
		{
			m_TimerToShowPlayers->Start();
		}
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
		if (m_TimerToShowPlayers != NULL)
		{
			m_TimerToShowPlayers->Start();
		}
		return true;
	}
	return false;
}

//Menu Button pressed
//---------------------------------------------------------------------//
bool PinballMaster::EventMenuButton(Object *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::EventMenuButton"));
	#endif


	if (m_Status == StatusPinball::attractmode)
	{
		if (m_Menu == NULL)
		{
			m_Menu = new Menu();
		}
		m_Status = StatusPinball::menusetup;
		m_Menu->PressButtonMenu();
	}
	else if (m_Status == StatusPinball::menutest || 
			 m_Status == StatusPinball::menusetup)
	{
		SetupTest(EVENT_TEST_EXIT_MENU);

		if (m_Menu != NULL)
		{
			delete m_Menu;
			m_Menu = NULL;
		}
	}

	return false;
}

//---------------------------------------------------------------------//
bool PinballMaster::EventEnterButton(Object *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::EventEnterButton"));
	#endif

	if (m_Status == StatusPinball::menusetup)
	{
		if (m_Menu != NULL)
		{
			m_Menu->PressButtonEnter();
		}
		return true;
	}
	else if (m_Status == StatusPinball::menutest)
	{
		SetupTest(EVENT_TEST_EXIT_MENU);
		if (m_Menu != NULL)
		{
			delete m_Menu;
			m_Menu = NULL;
		}

	}


	return false;
}

//---------------------------------------------------------------------//
bool PinballMaster::EventUpDownButton(Object *sender, bool upButton)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::EventUpDownButton"));
	#endif

	if (m_Status == StatusPinball::menusetup)
	{
		if (m_Menu != NULL)
		{
			m_Menu->PressUpDownButton(upButton);
		}
		return true;
	}
	else if (m_Status == StatusPinball::menutest)
	{
		if (m_Menu != NULL)
		{
			m_Menu->EventUpDownButton(sender, upButton);
		}
	}
	else
	{
		ChangeVolume(upButton);
	}

	return false;
}

//---------------------------------------------------------------------//
bool PinballMaster::PlayfieldEvent(Object *sender, uint8_t event, uint8_t value)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::PlayfieldEvent"));
	#endif

	if (m_Status == StatusPinball::playingmode && m_playerPlaying>= 0 && m_playerPlaying < MAX_PLAYERS)
	{
		//TODO: m_Players[m_playerPlaying]->NotifyEvent(sender, event, valueToSend);
		char szEvent[15];
		sprintf(szEvent, "%d", event);
		printText("event", szEvent, 0);
	}

	return true;
}

//---------------------------------------------------------------------//
bool PinballMaster::TimerIsOver(Object *sender)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::TimerIsOver"));
	#endif

	if (sender == m_TimerToShowPlayers && m_TimerToShowPlayers != NULL)
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
bool PinballMaster::SetupTest(uint8_t event)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::SetupTest"));
	#endif

	if (event == EVENT_TEST_EXIT_MENU)
	{
		if (m_Menu != NULL)
		{
			m_Menu->FinishTest();
			printText("Pinball", "OK", 0);
		}
		m_Status = StatusPinball::attractmode;
	}
	else if (event >= EVENT_TEST_INIT && event <= EVENT_TEST_FINISH)
	{
		if (event == EVENT_TEST_NBALLS3 || event == EVENT_TEST_NBALLS4 || event == EVENT_TEST_NBALLS5)
		{
			this->SetBallsByPlayer(3 + (event - EVENT_TEST_NBALLS3));
			printText("Set", "Ball", 1);
			delay(300);
			m_Status = StatusPinball::attractmode;
			return true;
		}
		else
		{
			Init(StatusPinball::menutest);
			if (m_Menu != NULL)
			{
				m_Menu->StartTest(event);
			}
		}
	}

	return true;
}

//---------------------------------------------------------------------//
void PinballMaster::StartGame(uint8_t Players)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::StartGame"));
	#endif
	this->Init(StatusPinball::playingmode);

	m_nPlayers = Players;

	printText("Player", "0", 0);
	m_Status = StatusPinball::playingmode;
	GetNewBall();

	m_playerPlaying = 0;

	if(m_TurnFlipperOn != NULL)
		m_TurnFlipperOn->TurnOn();
}

//---------------------------------------------------------------------//
void PinballMaster::PlayerLostBall()
//---------------------------------------------------------------------//
{
	GetNewBall();
}

//---------------------------------------------------------------------//
void PinballMaster::NextPlayer()
//---------------------------------------------------------------------//
{
}


//---------------------------------------------------------------------//
void PinballMaster::GetNewBall()
//---------------------------------------------------------------------//
{
	if (m_Status == StatusPinball::playingmode && m_OutBall != NULL)
	{
		m_OutBall->LanchBall();
	}
}

//---------------------------------------------------------------------//
void PinballMaster::ShowChooseNumberOfPlayers()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::ShowChooseNumberOfPlayers"));
	#endif

	if (m_Status == StatusPinball::getplayers)
	{
		char szPlayers[15];
		sprintf(szPlayers, "%d  %ds", m_nPlayers, m_nSecondsTimerToShowPlayers);
		printText("Players", szPlayers, 0);
	}
}

/*---------------------------------------------------------------------*/
bool PinballMaster::Loop(uint8_t value)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("PinballMaster::Loop"));
	#endif

	for (uint8_t i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Loop();
	}

	switch (m_Status)
	{
		case StatusPinball::attractmode:
		{
		}

		case StatusPinball::menusetup:
		case StatusPinball::menutest:
		{
			if (m_Menu != NULL)
			{
				m_Menu->Loop();
			}
		}
		break;
	}
	return true;
}

//-----------------------------------------------------------------------//
void PinballMaster::clearDisplay(uint8_t line)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballMaster::clearDisplay"));
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
	LogMessage(F("Pinball::printText"));
	#endif

	#ifdef DOS
	uint8_t xCursor, yCursor;
	getCursorXY(xCursor, yCursor);

	uint8_t x = 70;
	uint8_t y = 1;
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
	LogMessage(F("PinballMaster::DataReceived"));
	#endif
}

//---------------------------------------------------------------------//
void PinballMaster::PlaySongToInput(uint8_t portNumber)
//---------------------------------------------------------------------//
{
	if(m_Status == StatusPinball::playingmode)
	{
		switch (portNumber)
		{
		case INPUT_SW_OUTBALL1:
		case INPUT_SW_OUTBALL2:
			playSong(MP3_OUTBALL);
			break;

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
		case INPUT_ENTER_BUTTON:
			playSong(MP3_MENU_BUTTON);
			break;
		default:
			playSong(MP3_STARTBUTTONPORT);
			break;
		}
	}
}

