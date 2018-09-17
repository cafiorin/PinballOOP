/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Menu.h"
#include "Pinball.h"
#include "Event.h"

//-------------------------------------------------------//
Menu::Menu(PinballMaster *pinball)
//-------------------------------------------------------//
{
	m_PinballMaster = pinball;

	#ifdef DEBUGMESSAGES
	m_PinballMaster->LogMessage(F("Menu Constructor"));
	#endif

	m_isShowing = false;

	//Menu
	m_pMenu = new MenuString(NULL, -1, "Menu");
	MenuString *pTest = new MenuString(m_pMenu, -1, "Test");
	MenuString *pConfig = new MenuString(m_pMenu, -1, "Config");
	m_PinballMaster->LogMessage(F("Menu Constructor 1"));

	//Test
	MenuString *pLed = new MenuString(pTest, -1, "Led");
	MenuString *pCoin = new MenuString(pTest, -1, "Coin");
	MenuString *pOutput = new MenuString(pTest, -1, "Output");
	MenuString *pSound = new MenuString(pTest, -1, "Sound");
	m_PinballMaster->LogMessage(F("Menu Constructor 2"));

	//Config
	MenuString *pSfx = new MenuString(pConfig, -1, "SFX");
	MenuString *pNBalls = new MenuString(pConfig, -1, "Balls");
	m_PinballMaster->LogMessage(F("Menu Constructor 3"));

	//Led
	new MenuString(pLed, EVENT_TEST_LED_1BY1, "1 a 1");
	new MenuString(pLed, EVENT_TEST_LED_AUTO, "Auto");
	m_PinballMaster->LogMessage(F("Menu Constructor 4"));

	//Coin
	new MenuString(pCoin, EVENT_TEST_COIN_1BY1, "1 a 1");
	new MenuString(pCoin, EVENT_TEST_COIN_AUTO, "Auto");
	m_PinballMaster->LogMessage(F("Menu Constructor 5"));

	//Output
	new MenuString(pOutput, EVENT_TEST_OUTPUTS_1BY1, "1 a 1");
	new MenuString(pOutput, EVENT_TEST_OUTPUTS_AUTO, "Auto");
	m_PinballMaster->LogMessage(F("Menu Constructor 6"));

	//Sound
	new MenuString(pSound, EVENT_TEST_SOUND_BOARD1, "Board 1");
	new MenuString(pSound, EVENT_TEST_SOUND_BOARD2, "Board 2");
	m_PinballMaster->LogMessage(F("Menu Constructor 7"));

	//SFX
	new MenuString(pSfx, EVENT_TEST_SFX_ONOFF, "ON/OFF");
	m_PinballMaster->LogMessage(F("Menu Constructor 8"));

	//Balls
	new MenuString(pNBalls, EVENT_TEST_NBALLS3, "3");
	new MenuString(pNBalls, EVENT_TEST_NBALLS4, "4");
	new MenuString(pNBalls, EVENT_TEST_NBALLS5, "5");
	m_PinballMaster->LogMessage(F("Menu Constructor 9"));
}

//-------------------------------------------------------//
Menu::~Menu()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_PinballMaster->LogMessage(F("Menu Destructor"));
	#endif

	DestroyChildren(m_pMenu);
}

//-------------------------------------------------------//
void Menu::DestroyChildren(MenuString *pMenuString)
//-------------------------------------------------------//
{
	Vector<MenuString *> children = pMenuString->GetChildren();

	for(uint8_t i=0; i < children.size();i++)
	{
		DestroyChildren(children[i]);
	}

	delete pMenuString;
}

//-------------------------------------------------------//
bool Menu::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_PinballMaster->LogMessage(F("Menu::Init"));
	#endif

	m_isShowing = false;
	return true;
}


//-------------------------------------------------------//
void Menu::PressButtonMenu()
//-------------------------------------------------------//
{
	if (!m_isShowing)
	{
		m_isShowing = true;
		m_menuOptionSelected = m_pMenu;
		m_subOption = 0;
		m_subOptionSelected = m_pMenu->GetChildren()[0];
		m_backSelected = false;

		PrintMenu(ButtonPressed::start);
	}
	else
	{
		//Exit menu
		if (m_backSelected && m_menuOptionSelected->GetParent() == NULL)
		{
			m_PinballMaster->NotifyEvent(NULL, &Event(EVENT_TEST_EXIT_MENU));
			m_isShowing = false;
		}
		//Action
		else if (m_subOptionSelected->GetAction() != -1 && !m_backSelected)
		{
			m_PinballMaster->NotifyEvent(NULL, &Event(m_subOptionSelected->GetAction()));
			m_isShowing = false;
		}
		else
		{
			//Option Pressed
			if (!m_backSelected)
			{
				m_menuOptionSelected = m_subOptionSelected;
				m_subOption = 0;
				m_subOptionSelected = m_subOptionSelected->GetChildren()[0];
			}
			else
			{
				//Pressed Back
				m_menuOptionSelected = m_menuOptionSelected->GetParent();
				m_subOption = 0;
				m_subOptionSelected = m_subOptionSelected->GetChildren()[0];
				m_backSelected = false;
			}
			PrintMenu(ButtonPressed::start);
		}
	}
}


//-------------------------------------------------------//
void Menu::PressButtonEnter()
//-------------------------------------------------------//
{
	if (!m_isShowing)
	{
		m_isShowing = true;
		m_menuOptionSelected = m_pMenu;
		m_subOption = 0;
		m_subOptionSelected = m_pMenu->GetChildren()[0];
		m_backSelected = false;

		PrintMenu(ButtonPressed::start);
	}
	else
	{
		//Exit menu
		if (m_backSelected && m_menuOptionSelected->GetParent() == NULL)
		{
			m_PinballMaster->NotifyEvent(NULL, &Event(EVENT_TEST_EXIT_MENU));
			m_isShowing = false;
		}
		//Action
		else if (m_subOptionSelected->GetAction() != -1 && !m_backSelected)
		{
			m_PinballMaster->NotifyEvent(NULL, &Event(m_subOptionSelected->GetAction()));
			m_isShowing = false;
		}
		else
		{
			//Option Pressed
			if (!m_backSelected)
			{
				m_menuOptionSelected = m_subOptionSelected;
				m_subOption = 0;
				m_subOptionSelected = m_subOptionSelected->GetChildren()[0];
			}
			else
			{
				//Pressed Back
				m_menuOptionSelected = m_menuOptionSelected->GetParent();
				m_subOption = 0;
				m_subOptionSelected = m_subOptionSelected->GetChildren()[0];
				m_backSelected = false;
			}
			PrintMenu(ButtonPressed::start);
		}
	}
}

//-------------------------------------------------------//
void Menu::PrintMenu(ButtonPressed button)
//-------------------------------------------------------//
{
	MenuString *pMenuString = m_menuOptionSelected;
	char *szLine1 = pMenuString->GetString();

	Vector<MenuString *> children = pMenuString->GetChildren();

	if (m_backSelected)
	{
		if (button == ButtonPressed::up)
			m_subOption = 0;
	}

	if(m_subOption >= children.size() || m_subOption < 0)
	{
		m_subOption = (int) children.size();
		m_PinballMaster->printText(szLine1, "Voltar", 0);
		m_backSelected = true;
		return;
	}

	char *szLine2 = children[m_subOption]->GetString();
	m_subOptionSelected = children[m_subOption];
	m_PinballMaster->printText(szLine1, szLine2, 0);
	m_backSelected = false;
}

//-------------------------------------------------------//
bool Menu::PressUpDownButton(bool upButton)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_PinballMaster->LogMessage(F("Menu::PressButton"));
	#endif

	if (upButton)
	{
		m_subOption++;
		PrintMenu(ButtonPressed::up);
		return true;
	}
	else
	{
		m_subOption--;
		PrintMenu(ButtonPressed::down);
		return true;
	}

	return false;
}

