#ifndef Door__INCLUDED_
#define Door__INCLUDED_

class Button;
#include "Observer.h"

class Door
{
public:
	Door(Observer* observer);
	~Door();
	Button* GetMenuButton() { return m_MenuButton; }
	Button* GetUpButton() { return m_UpButton; }
	Button* GetDownButton() { return m_DownButton; }
	Button* GetEnterButton() {return m_EnterButton;}

	Button* GetStartButton() { return m_StartButton; }

private:
	Button* m_MenuButton;
	Button* m_UpButton;
	Button* m_DownButton;
	Button* m_EnterButton;

	Button* m_StartButton;

};
#endif
