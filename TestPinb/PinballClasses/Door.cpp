#include "Door.h"
#include "Button.h"
#include "..\\OOP\\defines.h"

//-------------------------
Door::Door(Observer *observer)
//-------------------------
{
	m_MenuButton = new Button(INPUT_MENU_BUTTON, observer);
	m_UpButton = new Button(INPUT_UP_BUTTON, observer);
	m_DownButton = new Button(INPUT_DOWN_BUTTON, observer);
	m_EnterButton = new Button(INPUT_ENTER_BUTTON, observer);
}

//-------------------------
Door::~Door()
//-------------------------
{
	delete m_MenuButton;
	delete m_UpButton;
	delete m_DownButton;
	delete m_EnterButton;
}


