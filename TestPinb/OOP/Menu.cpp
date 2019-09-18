/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Menu.h"
#include "Pinball.h"
#include "SelfTest.h"

//-------------------------------------------------------//
Menu::Menu() 
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Menu Constructor"));
	#endif
	m_SelfTest = new SelfTest();
	m_isShowing = false;

	//Menu
	m_pMenu = new MenuString(NULL, EVENT_NULL, "Menu");
	MenuString *pTest = new MenuString(m_pMenu, EVENT_NULL, "Test");
	MenuString *pConfig = new MenuString(m_pMenu, EVENT_NULL, "Config");

	//Test
	MenuString *pLed = new MenuString(pTest, EVENT_NULL, "Led");
	MenuString *pCoin = new MenuString(pTest, EVENT_NULL, "Coin");
	MenuString *pOutput = new MenuString(pTest, EVENT_NULL, "Output");
	MenuString* pInput = new MenuString(pTest, EVENT_NULL, "Input");
	MenuString *pSound = new MenuString(pTest, EVENT_NULL, "Sound");

	//Config
	MenuString *pSfx = new MenuString(pConfig, EVENT_NULL, "SFX");
	MenuString *pNBalls = new MenuString(pConfig, EVENT_NULL, "Balls");

	//Led
	new MenuString(pLed, EVENT_TEST_LED_1BY1, "1 a 1");
	new MenuString(pLed, EVENT_TEST_LED_AUTO, "Auto");

	//Coin
	new MenuString(pCoin, EVENT_TEST_COIN_1BY1, "1 a 1");
	new MenuString(pCoin, EVENT_TEST_COIN_AUTO, "Auto");

	//Output
	new MenuString(pOutput, EVENT_TEST_OUTPUTS_1BY1, "1 a 1");
	new MenuString(pOutput, EVENT_TEST_OUTPUTS_AUTO, "Auto");

	//Input
	new MenuString(pInput, EVENT_TEST_INPUTS_1BY1, "1 a 1");
	new MenuString(pInput, EVENT_TEST_INPUTS_AUTO, "Auto");

	//Sound
	new MenuString(pSound, EVENT_TEST_SOUND_BOARD1, "Board 1");
	new MenuString(pSound, EVENT_TEST_SOUND_BOARD2, "Board 2");

	//SFX
	new MenuString(pSfx, EVENT_TEST_SFX_ONOFF, "ON/OFF");

	//Balls
	new MenuString(pNBalls, EVENT_TEST_NBALLS3, "3");
	new MenuString(pNBalls, EVENT_TEST_NBALLS4, "4");
	new MenuString(pNBalls, EVENT_TEST_NBALLS5, "5");
}

//-------------------------------------------------------//
Menu::~Menu()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Menu Destructor"));
	#endif

	DestroyChildren(m_pMenu);
	delete m_SelfTest;
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
	LogMessage(F("Menu::Init"));
	#endif

	m_isShowing = false;
	return true;
}


//-------------------------------------------------------//
void Menu::PressButtonMenu()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Menu::PressButtonMenu"));
	#endif

	if (!m_isShowing)
	{
		m_isShowing = true;
		m_menuOptionSelected = m_pMenu;
		m_subOption = 0;
		m_subOptionSelected = m_pMenu->GetChildren()[0];
		m_backSelected = false;

		PrintMenu(ButtonPressed::menu);
	}
	else
	{
		//Exit menu
		m_Pinball->NotifyEvent(this, EVENT_TEST_EXIT_MENU,0);
		m_isShowing = false;
	}
}


//-------------------------------------------------------//
void Menu::PressButtonEnter()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Menu::PressButtonEnter"));
	#endif

	if (m_isShowing)
	{
		if (m_backSelected && m_menuOptionSelected->GetParent() == NULL)
		{
			m_Pinball->NotifyEvent(this, EVENT_TEST_EXIT_MENU,0);
			m_isShowing = false;
		}
		//Action
		else if (m_subOptionSelected->GetAction() != EVENT_NULL && !m_backSelected)
		{
			m_Pinball->NotifyEvent(this, m_subOptionSelected->GetAction(),0);
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

			PrintMenu(ButtonPressed::menu);
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
	LogMessage(F("Menu::PressButton"));
	#endif

	if (upButton)
	{
		m_subOption++;
		PrintMenu(ButtonPressed::up);
	}
	else
	{
		m_subOption--;
		PrintMenu(ButtonPressed::down);
	}

	return true;
}

//-------------------------------------------------------//
void Menu::EventUpDownButton(Object *sender, bool upButton)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Menu::EventUpDownButton"));
	#endif
	
	m_SelfTest->EventUpDownButton(sender, upButton);
}

//-------------------------------------------------------//
void Menu::StartTest(uint8_t event)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("Menu::StartTest"));
	#endif

	if (m_SelfTest != NULL)
	{
		m_SelfTest->StartTest(event);
	}
}

//-------------------------------------------------------//
void Menu::FinishTest()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	m_Pinball->LogMessage(F("Menu::FinishTest"));
	#endif

	if (m_SelfTest != NULL)
	{
		m_SelfTest->FinishTest();
	}
}

//---------------------------------------------------------------------//
void Menu::Loop()
//---------------------------------------------------------------------//
{
	m_SelfTest->Loop();
}

//---------------------------------------------------------------------//
void Menu::EventToInput(Object* sender, uint8_t event, uint8_t valueToSend)
//---------------------------------------------------------------------//
{
	m_SelfTest->EventToInput(sender, event, valueToSend);
}
