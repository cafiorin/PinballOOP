#include "PinballMachine.h"
#include "HardwareSerial.h"
#include "Logger.h"
#include "Menu.h"

#include "LatchOutputs.h"
#include "MultiplexInputs.h"
#include "Door.h"

#include "Observer.h"
#include "Initializable.h"
#include "Runnable.h"
#include "ChangeableStatus.h"

#include "Playfield.h"
#include "LedControl.h"
#include "NewTimer.h"

#include "defines.h"
#include "definesMP3.h"
#include "Logger.h"

#ifdef ARDUINOLIB
#include "Arduino.h"
#include "ht1632pinball.h"
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#endif


DFRobotDFPlayerMini* PinballMachine::m_playerMain = NULL;
DFRobotDFPlayerMini* PinballMachine::m_playerSFX = NULL;
LiquidCrystal_I2C* PinballMachine::m_lcd = NULL;


//----------------------------------------
PinballMachine::PinballMachine() : Observer()
//----------------------------------------
{
}

#ifdef DOS
//----------------------------------------
void PinballMachine::Setup(HardwareSerial* serial)
//----------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("PinballMachine Setup"));
	#endif
	m_Serial = serial;
	m_Logger = new Logger(m_Serial);

	printText("Pinball", "init", 0);
	CreateObjects();
	Initialize();
}
#endif

#ifdef ARDUINOLIB
//----------------------------------------
void PinballMachine::Setup(DFRobotDFPlayerMini *DFPlayerMain, DFRobotDFPlayerMini* DFPlayerSFX, HardwareSerial* serial, LiquidCrystal_I2C *lcd)
//----------------------------------------
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("PinballMachine Setup"));
	#endif

	m_Serial = serial;
	m_Logger = new Logger(m_Serial);
	m_playerMain = DFPlayerMain;
	m_playerSFX = DFPlayerSFX;

	//m_playerMain->volume(5); //(0-30)
	//m_playerSFX->volume(10);
	m_lcd = lcd;

	ht1632_setup();

	printText("Pinball", "init", 0);
	CreateObjects();
	Initialize();
}
#endif // ARDUINOLIB


//----------------------------------------
PinballMachine::~PinballMachine()
//----------------------------------------
{
	delete m_muxInputs;
	delete m_LatchOutputLowVoltage;
	delete m_LatchOutputHighVoltage;
	delete m_LedControl;
	delete m_Logger;

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
	m_LatchOutputHighVoltage = new LatchOutputs(LatchOutputHighSER, LatchOutputHighSRCLK, LatchOutputHighRCLK, RESET_LATCH);
	m_LatchOutputLowVoltage = new LatchOutputs(LatchOutputLowSER, LatchOutputLowSRCLK, LatchOutputLowRCLK, RESET_LATCH);
	m_muxInputs = new MultiplexInputs(/*S0*/23, /*S1*/25, /*S2*/27,/*S3*/29, /*SIn0*/22, /*SIn1*/24, /*SIn2*/26);
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
	ChangeStatus(StatusPinballMachine::initializing);
	m_nBallByPlayer = MAX_BALLS;
	m_enableSfx = true;
	m_nSecondsTimerToShowPlayers = 5;
}

//---------------------------------------------------------------------
void PinballMachine::ChangeStatus(StatusPinballMachine status)
//---------------------------------------------------------------------
{
	m_Status = status;
	ChangeableStatus::ChangeStatusAll(status);
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
	
	case EventType::MenuOptionSelected:
		SetupTest(value);
		break;

	case EventType::TimeIsOver:
		TimerIsOver();
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
	case INPUT_MENU_BUTTON_DEBUG:
		EventMenuButton();
		break;

	case INPUT_UP_BUTTON:
	case INPUT_UP_BUTTON_DEBUG:
		EventUpDownButton(true);
		break;

	case INPUT_DOWN_BUTTON:
	case INPUT_DOWN_BUTTON_DEBUG:
		EventUpDownButton(false);
		break;

	case INPUT_ENTER_BUTTON:
	case INPUT_ENTER_BUTTON_DEBUG:
		EventEnterButton();
		break;

	case INPUT_START_BUTTON:
		EventStartButton();
		break;

	default:
		break;
	}
}


void PinballMachine::Initialize()
{
	Initializable::initAll();

	printText("Pinball", "OK", 0);
	delay(200);
	ChangeStatus(StatusPinballMachine::attractmode);
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

		ChangeStatus(StatusPinballMachine::getplayers);
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
		ChangeStatus(StatusPinballMachine::menusetup);
		m_Menu->PressButtonMenu();
	}
	else if (m_Status == StatusPinballMachine::menutest ||
		m_Status == StatusPinballMachine::menusetup)
	{
		SetupTest(EVENT_TEST_EXIT_MENU);
		m_Menu->PressButtonMenu();
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
		ChangeStatus(StatusPinballMachine::attractmode);
	}
	else if (event >= EVENT_TEST_INIT && event <= EVENT_TEST_FINISH)
	{
		if (event == EVENT_TEST_NBALLS3 || event == EVENT_TEST_NBALLS4 || event == EVENT_TEST_NBALLS5)
		{
			this->SetBallsByPlayer(3 + (event - EVENT_TEST_NBALLS3));
			printText("Set", "Ball", 1);
			delay(300);
			ChangeStatus(StatusPinballMachine::attractmode);

		}
		else
		{
			ChangeStatus(StatusPinballMachine::menutest);
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
	ChangeStatus(StatusPinballMachine::initplaymode);

	m_nPlayers = Players;

	printText("Player", "0", 0);
	ChangeStatus(StatusPinballMachine::playingmode);
	m_playerPlaying = 0;
	
	m_Playfield->StartGame();
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

#ifdef LCD
	if (m_lcd != NULL)
	{
		m_lcd->setCursor(0, 0);
		m_lcd->print("                ");
		m_lcd->setCursor(0, 0);
		m_lcd->print(text1);
		m_lcd->setCursor(0, 1);
		m_lcd->print("                ");
		m_lcd->setCursor(0, 1);
		m_lcd->print(text2);
	}
#endif // LCD

#endif
}

//---------------------------------------------------------------------//
void PinballMachine::PlaySongToInput(byte portNumber)
//---------------------------------------------------------------------//
{
	switch (portNumber)
	{
	case INPUT_SW_OUTBALL1:
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

//----------------------------------------------------//
void PinballMachine::playSong(int number, bool SFX/*=false*/)
//-----------------------------------------------------------------------//
{
#ifdef DOS
#ifdef DEBUGMESSAGES
	char szMsg[30]; //12 + 10 + 1
	sprintf(szMsg, "Play song:%d", number);
	Logger::LogMessage(szMsg);
#endif 
#endif

#ifdef ARDUINOLIB
	if (!SFX && m_playerMain != NULL)
	{
		m_playerMain->play(number);
	}
	else if (SFX && m_playerSFX != NULL)
	{
		m_playerSFX->play(number);
	}

#endif // ARDUINOLIB
}

//-----------------------------------------------------------------------//
void PinballMachine::ChangeVolume(bool plus)
//-----------------------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("Pinball::ChangeVolume"));
	Logger::LogMessage(F("Change Volume"));
	#endif

	#ifdef ARDUINOLIB
	if (m_playerMain != NULL)
	{
		if (plus)
			m_playerMain->volumeUp();
		else
			m_playerMain->volumeDown();
	}

	if (m_playerSFX != NULL)
	{
		if (plus)
			m_playerSFX->volumeUp();
		else
			m_playerSFX->volumeDown();
	}
	#endif // ARDUINOLIB
}