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
	m_line1 = 0;
	m_line2 = 0;

	return false;
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



char szLine1[10] = "Menu";
char szLine2[10] = "Test>";

char* Menu::GetMenuLine1()
{
	//TODO: Get from Array
	return szLine1;
}

char* Menu::GetMenuLine2()
{
	//TODO: GetFrom Array
	return szLine2;
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

