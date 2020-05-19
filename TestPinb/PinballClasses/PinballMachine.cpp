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
	LogMessage(F("PinballMachine Construtor"));
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
	m_Playfield = new Playfield(this,m_muxInputs,m_LatchOutputLowVoltage,m_LatchOutputHighVoltage,m_LedControl);

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
	case INPUT_DOWN_BUTTON:
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
	LogMessage(F("PinballMaster::EventStartButton"));
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
	LogMessage(F("PinballMaster::EventMenuButton"));
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
	LogMessage(F("PinballMaster::EventEnterButton"));
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
	LogMessage(F("PinballMaster::EventUpDownButton"));
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
	LogMessage(F("PinballMaster::SetupTest"));
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
	LogMessage(F("PinballMaster::TimerIsOver"));
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
	LogMessage(F("PinballMaster::StartGame"));
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
	LogMessage(F("PinballMaster::ShowChooseNumberOfPlayers"));
	#endif

	if (m_Status == StatusPinballMachine::getplayers)
	{
		char szPlayers[15];
		sprintf(szPlayers, "%d  %ds", m_nPlayers, m_nSecondsTimerToShowPlayers);
		printText("Players", szPlayers, 0);
	}
}
