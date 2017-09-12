/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Menu.h"
#include "Pinball.h"

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

	return false;
}


#define KeyUp 40
#define KeyDown 41
char szLine1[10] = "Line1";
char szLine2[10] = "Line2";

char* Menu::GetMenuLine1()
{
	return szLine1;
}

char* Menu::GetMenuLine2()
{
	return szLine2;
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

	if (value == KeyUp)
	{
		char *szLine1 = GetMenuLine1();
		char *szLine2 = GetMenuLine2();
		m_pinball->printText(szLine1, szLine2, 0);
	}
	else if (value == KeyDown)
	{

	}

	return false;
}

