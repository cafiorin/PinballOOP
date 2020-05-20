#include "PinballMachine.h"
#include "HardwareSerial.h"
#include "Menu.h"

#include "LatchOutputs.h"
#include "MultiplexInputs.h"
#include "Door.h"
#include "Observer.h"
#include "Initializable.h"
#include "Runnable.h"
#include "Playfield.h"
#include "LedControl.h"
#include "NewTimer.h"

#include "defines.h"
#include "definesMP3.h"
#include "Logger.h"

#ifdef ARDUINOLIB
#include "ht1632pinball.h"
#endif


//----------------------------------------
PinballMachine::PinballMachine(HardwareSerial* serial) : Observer()
//----------------------------------------
{
	m_Serial = serial;

	#ifdef ARDUINOLIB
	ht1632_setup();
	#endif

	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("PinballMachine Construtor"));
	#endif
	
	CreateObjects();
	Initialize();
}

//----------------------------------------
PinballMachine::~PinballMachine()
//----------------------------------------
{
	delete m_muxInputs;
	delete m_LatchOutputLowVoltage;
	delete m_LatchOutputHighVoltage;
	delete m_LedControl;

	//delete m_Sequencer;

	delete m_Door;
	delete m_Playfield;
	delete m_Menu;
	
	delete m_TimerToShowPlayers;
}

//----------------------------------------
void PinballMachine::CreateObjects()
//----------------------------------------
{
	m_muxInputs = new MultiplexInputs(/*S0*/23, /*S1*/25, /*S2*/27,/*S3*/29, /*SIn0*/22, /*SIn1*/34, /*SIn2*/36);
	m_LatchOutputLowVoltage = new LatchOutputs(A4, A5, A3);
	m_LatchOutputHighVoltage = new LatchOutputs(A8, A9, A10); // TODO: Fix this values
	m_LedControl = new LedControl();
	
	//m_Sequencer = new Sequencer()

	m_Door = new Door(this);
	m_Playfield = new Playfield(m_muxInputs,m_LatchOutputLowVoltage,m_LatchOutputHighVoltage,m_LedControl);

	m_TimerToShowPlayers = new NewTimer(1000, NewTimerType::continuous, this);

	InitVars();
}

//---------------------------------------------------------------------
void PinballMachine::InitVars()
//---------------------------------------------------------------------
{
	m_Menu = NULL;
	m_Status = StatusPinballMachine::initializing;
	m_nBallByPlayer = MAX_BALLS;
	m_enableSfx = true;
	m_nSecondsTimerToShowPlayers = 5;
}

//---------------------------------------------------------------------
void PinballMachine::onNotifySubject(EventType event, byte value)
//---------------------------------------------------------------------
{
	switch (event)
	{
	case EventType::Pressed:
		ButtonPressed(value);
		break;
	
	default:
		break;
	}
}

//---------------------------------------------------------------------
void PinballMachine::ButtonPressed(byte value)
//---------------------------------------------------------------------
{
	switch (value)
	{
	case INPUT_MENU_BUTTON:
		EventMenuButton();
		break;

	case INPUT_UP_BUTTON:
		EventUpDownButton(true);
		break;

	case INPUT_DOWN_BUTTON:
		EventUpDownButton(false);
		break;

	case INPUT_ENTER_BUTTON:
		EventEnterButton();
		break;
	default:
		break;
	}
}


void PinballMachine::Initialize()
{
	Initializable::initAll();
}

void PinballMachine::Loop()
{
	Runnable::loopAll();
}


//---------------------------------------------------------------------//
void PinballMachine::EventStartButton()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::EventStartButton"));
	#endif

	if (m_Status == StatusPinballMachine::attractmode)
	{
		if (m_TimerToShowPlayers != NULL)
		{
			m_TimerToShowPlayers->Start();
		}
		m_Status = StatusPinballMachine::getplayers;
		m_nPlayers = 1;
		m_nSecondsTimerToShowPlayers = 5;
		ShowChooseNumberOfPlayers();
	}
	else if (m_Status == StatusPinballMachine::getplayers)
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
	}
}


//---------------------------------------------------------------------//
void PinballMachine::EventMenuButton()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::EventMenuButton"));
	#endif

	if (m_Status == StatusPinballMachine::attractmode)
	{
		if (m_Menu == NULL)
		{
			m_Menu = new Menu(this);
		}
		m_Status = StatusPinballMachine::menusetup;
		m_Menu->PressButtonMenu();
	}
	else if (m_Status == StatusPinballMachine::menutest ||
		m_Status == StatusPinballMachine::menusetup)
	{
		SetupTest(EVENT_TEST_EXIT_MENU);

		if (m_Menu != NULL)
		{
			delete m_Menu;
			m_Menu = NULL;
		}
	}
}

//---------------------------------------------------------------------//
void PinballMachine::EventEnterButton()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::EventEnterButton"));
	#endif

	if (m_Status == StatusPinballMachine::menusetup)
	{
		if (m_Menu != NULL)
		{
			m_Menu->PressButtonEnter();
		}
	}
	else if (m_Status == StatusPinballMachine::menutest)
	{
		SetupTest(EVENT_TEST_EXIT_MENU);
		if (m_Menu != NULL)
		{
			delete m_Menu;
			m_Menu = NULL;
		}

	}
}

//---------------------------------------------------------------------//
void PinballMachine::EventUpDownButton(bool upButton)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::EventUpDownButton"));
	#endif

	if (m_Status == StatusPinballMachine::menusetup)
	{
		if (m_Menu != NULL)
		{
			m_Menu->PressUpDownButton(upButton);
		}
	}
	else if (m_Status == StatusPinballMachine::menutest)
	{
		if (m_Menu != NULL)
		{
			m_Menu->EventUpDownButton(upButton);
		}
	}
	else
	{
		ChangeVolume(upButton);
	}
}

//---------------------------------------------------------------------//
void PinballMachine::SetupTest(byte event)
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::SetupTest"));
	#endif

	if (event == EVENT_TEST_EXIT_MENU)
	{
		if (m_Menu != NULL)
		{
			m_Menu->FinishTest();
			printText("Pinball", "OK", 0);
		}
		m_Status = StatusPinballMachine::attractmode;
	}
	else if (event >= EVENT_TEST_INIT && event <= EVENT_TEST_FINISH)
	{
		if (event == EVENT_TEST_NBALLS3 || event == EVENT_TEST_NBALLS4 || event == EVENT_TEST_NBALLS5)
		{
			this->SetBallsByPlayer(3 + (event - EVENT_TEST_NBALLS3));
			printText("Set", "Ball", 1);
			delay(300);
			m_Status = StatusPinballMachine::attractmode;
		}
		else
		{
			if (m_Menu != NULL)
			{
				m_Menu->StartTest(event);
			}
		}
	}
}

//---------------------------------------------------------------------//
void PinballMachine::TimerIsOver()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::TimerIsOver"));
	#endif

	m_nSecondsTimerToShowPlayers--;
	ShowChooseNumberOfPlayers();
	if (m_nSecondsTimerToShowPlayers <= 0)
	{
		m_TimerToShowPlayers->Stop();
		StartGame(m_nPlayers);
	}
}

//---------------------------------------------------------------------//
void PinballMachine::StartGame(byte Players)
//---------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::StartGame"));
#endif
	//TODO: this->Init(StatusPinball::playingmode);

	m_nPlayers = Players;

	printText("Player", "0", 0);
	m_Status = StatusPinballMachine::playingmode;
	//GetNewBall();

	m_playerPlaying = 0;

	//if (m_TurnFlipperOn != NULL)
	//	m_TurnFlipperOn->TurnOn();
}


//---------------------------------------------------------------------//
void PinballMachine::ShowChooseNumberOfPlayers()
//---------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::ShowChooseNumberOfPlayers"));
	#endif

	if (m_Status == StatusPinballMachine::getplayers)
	{
		char szPlayers[15];
		sprintf(szPlayers, "%d  %ds", m_nPlayers, m_nSecondsTimerToShowPlayers);
		printText("Players", szPlayers, 0);
	}
}

//-----------------------------------------------------------------------//
void PinballMachine::clearDisplay(byte line)
//-----------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("PinballMaster::clearDisplay"));
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
void PinballMachine::printText(char* text1, char* text2, char font)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("Pinball::printText"));
	#endif

#ifdef DOS
	byte xCursor, yCursor;
	getCursorXY(xCursor, yCursor);

	byte x = 70;
	byte y = 1;
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
void PinballMachine::PlaySongToInput(byte portNumber)
//---------------------------------------------------------------------//
{
	if (m_Status == StatusPinballMachine::playingmode)
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

//----------------------------------------------------//
void PinballMachine::playSong(char song[], bool priority /*default=true*/)
//-----------------------------------------------------------------------//
{
#ifdef DOS
#ifdef DEBUGMESSAGES
	char szMsg[30]; //12 + 10 + 1
	sprintf(szMsg, "Play song:%s", song);
	Logger::LogMessage(szMsg);
#endif 
#endif

#ifdef ARDUINOLIB
	if (song != NULL && m_MP3player != NULL)
	{
		if (priority && m_MP3player->getState() == playback)
		{
			m_MP3player->stopTrack();
		}

		int8_t result = m_MP3player->playMP3(song);
		if (result != 0)
		{
#ifdef DOS
			char szMsg[50];
			sprintf(szMsg, "Error code: %d when trying to play track", result);
			LogMessage(szMsg);
#endif	
		}
	}
#endif // ARDUINOLIB
}

//-----------------------------------------------------------------------//
void PinballMachine::ChangeVolume(bool plus, byte delta /*default = 5*/)
//-----------------------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("Pinball::ChangeVolume"));
	Logger::LogMessage(F("Change Volume"));
#endif

#ifdef ARDUINOLIB
	if (m_MP3player != NULL)
	{
		union twobyte mp3_vol;
		mp3_vol.word = m_MP3player->getVolume();
		uint8_t volume = mp3_vol.byte[1];
		if (plus)
			volume += delta;
		else
			volume -= delta;

		if (volume >= 254)
		{
			volume = 254;
		}
		else if (volume <= 2)
		{
			volume = 2;
		}

		m_MP3player->setVolume(volume, volume);
	}
#endif // ARDUINOLIB
}