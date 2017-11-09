/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Menu.h"
#include "Pinball.h"

#define MenuBtn 39
#define KeyUp 40
#define KeyDown 41

//-------------------------------------------------------//
Menu::Menu(const char *szName, Pinball *pinball) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Menu Constructor");
	#endif

	Init();
}

//-------------------------------------------------------//
Menu::~Menu()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Menu Destructor");
	#endif
}

//-------------------------------------------------------//
bool Menu::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("Menu::Init");
	#endif
	
	m_enabled = true;
	m_isShowing = false;
	m_option = 0;
	m_subOption = 0;

	return true;
}


void Menu::StartMenu()
{
	if (!m_isShowing)
	{
		m_isShowing = true;
		m_option = 0;
		m_subOption = 0;

		PrintMenu();
	}
	else
	{
		//TODO: Select
		//if(Action)
		//else
		//{
		//	m_option++;
		//}
	}
}


int optionQuant[] = { 2,3,3 };

char* Menu::GetMenuLine1()
{
	/*
	switch (m_option)
	{
		case 0:
			return "Menu";
		case 1:
			return "Test";
		case 2:
			return "Config";
	}
	return "";
	*/
	return NULL;
}

char* Menu::GetMenuLine2()
{
	/*
	switch (m_option)
	{
	case 0:
		switch (m_subOption)
		{
		case 0:
			return "Test";
		case 1:
			return "Config";
		}
	case 1:
		switch (m_subOption)
		{
		case 0:
			return "Led";
		case 1:
			return "Bobina";
		case 2:
			return "Som";
		}
	case 2:
		switch (m_subOption)
		{
		case 0:
			return "Volume";
		case 1:
			return "SFX";
		case 2:
			return "Balls";
		}
	}
	return "";
	*/

	return NULL;
}


void Menu::PrintMenu()
{
	char *szLine1 = GetMenuLine1();
	char *szLine2 = GetMenuLine2();
	m_pinball->printText(szLine1, szLine2, 0);
}

void Menu::GetNextOption()
{
	//TODO:
	m_subOption++;
}

void Menu::GetPrevOption()
{
	//TODO:
	m_subOption++;
}

//-------------------------------------------------------//
bool Menu::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("Menu::Loop");
		#endif
	}

	if (value == MenuBtn)
	{
		//TODO:
		PrintMenu();
	}
	else if (value == KeyUp)
	{
		//TODO:
		GetNextOption();
		PrintMenu();
	}
	else if (value == KeyDown)
	{
		//TODO:
		GetPrevOption();
		PrintMenu();
	}

	return false;
}

