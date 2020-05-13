#include "Door.h"
#include "Button.h"
#include "..\\OOP\\defines.h"

//-------------------------
Door::Door()
//-------------------------
{
	m_MenuButton = new Button(INPUT_MENU_BUTTON);
	m_UpButton = new Button(INPUT_UP_BUTTON);
	m_DownButton = new Button(INPUT_DOWN_BUTTON);
	m_EnterButton = new Button(INPUT_ENTER_BUTTON);
}

//-------------------------
Door::~Door()
//-------------------------
{

}
