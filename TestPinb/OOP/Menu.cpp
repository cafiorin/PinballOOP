/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Menu.h"
#include "Pinball.h"

//-------------------------------------------------------//
Menu::Menu(const char *szName, PinballMaster *pinball) 
//-------------------------------------------------------//
{
	m_Pinball = pinball;
	
	#ifdef DEBUGMESSAGES
	m_Pinball->Debug("Menu Constructor");
	#endif


	Init();
}

//-------------------------------------------------------//
Menu::~Menu()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_Pinball->Debug("Menu Destructor");
	#endif
}

//-------------------------------------------------------//
bool Menu::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_Pinball->Debug("Menu::Init");
	#endif
	
	m_isShowing = false;

	//Menu
	m_pMenu = new MenuString(NULL, -1, "Menu");
	MenuString *pTest = new MenuString(m_pMenu, -1, "Test");
	MenuString *pConfig = new MenuString(m_pMenu, -1, "Config");

	//Test
	MenuString *pLed = new MenuString(pTest, -1, "Led");
	MenuString *pCoin = new MenuString(pTest, -1, "Bobina");
	MenuString *pSound = new MenuString(pTest, -1, "Som");

	//Config
	MenuString *pSfx = new MenuString(pConfig, -1, "SFX");
	MenuString *pNBalls = new MenuString(pConfig, -1, "Bolas");

	//Led
	new MenuString(pLed, EVENT_TEST_LED_1BY1, "1 a 1");
	new MenuString(pLed, EVENT_TEST_LED_AUTO, "Auto");

	//Bobina
	new MenuString(pCoin, EVENT_TEST_COIN_1BY1, "1 a 1");
	new MenuString(pCoin, EVENT_TEST_COIN_AUTO, "Auto");

	//Som
	new MenuString(pSound, EVENT_TEST_SOUND_BOARD1, "Placa 1");
	new MenuString(pSound, EVENT_TEST_SOUND_BOARD2, "Placa 2");

	//SFX
	new MenuString(pSfx, EVENT_TEST_SFX_ONOFF, "ON/OFF");

	//Bolas
	new MenuString(pNBalls, EVENT_TEST_NBALLS3, "3");
	new MenuString(pNBalls, EVENT_TEST_NBALLS4, "4");
	new MenuString(pNBalls, EVENT_TEST_NBALLS5, "5");

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
			m_Pinball->NotifyEvent(NULL, EVENT_TEST_EXIT_MENU, 0);
			m_isShowing = false;
		}
		//Action
		else if (m_subOptionSelected->GetAction() != -1 && !m_backSelected)
		{
			m_Pinball->NotifyEvent(NULL, m_subOptionSelected->GetAction(), 0);
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
		m_subOption = children.size();
		m_Pinball->printText(szLine1, "Voltar", 0);
		m_backSelected = true;
		return;
	}

	char *szLine2 = children[m_subOption]->GetString();
	m_subOptionSelected = children[m_subOption];
	m_Pinball->printText(szLine1, szLine2, 0);
	m_backSelected = false;
}

//-------------------------------------------------------//
bool Menu::PressUpDownButton(bool upButton)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_Pinball->Debug("Menu::PressButton");
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

