#include "Door.h"
#include "Button.h"
#include "defines.h"

//-------------------------
Door::Door(Observer *observer)
//-------------------------
{
	m_MenuButton = new Button(INPUT_MENU_BUTTON, observer);
	m_UpButton = new Button(INPUT_UP_BUTTON, observer);
	m_DownButton = new Button(INPUT_DOWN_BUTTON, observer);
	m_EnterButton = new Button(INPUT_ENTER_BUTTON, observer);

	m_MenuButtonDebug = new Button(INPUT_MENU_BUTTON_DEBUG, observer);
	m_UpButtonDebug = new Button(INPUT_UP_BUTTON_DEBUG, observer);
	m_DownButtonDebug = new Button(INPUT_DOWN_BUTTON_DEBUG, observer);
	m_EnterButtonDebug = new Button(INPUT_ENTER_BUTTON_DEBUG, observer);

	m_StartButton = new Button(INPUT_START_BUTTON, observer);
}

//-------------------------
Door::~Door()
//-------------------------
{
	delete m_MenuButton;
	delete m_UpButton;
	delete m_DownButton;
	delete m_EnterButton;

	delete m_MenuButtonDebug;
	delete m_UpButtonDebug;
	delete m_DownButtonDebug;
	delete m_EnterButtonDebug;


	delete m_StartButton;
}

