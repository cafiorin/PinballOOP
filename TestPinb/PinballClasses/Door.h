#ifndef Door__INCLUDED_
#define Door__INCLUDED_

class Button;
#include "Observer.h"

class Door
{
public:
	Door(Observer* observer);
	~Door();

private:
	Button* m_MenuButton;
	Button* m_UpButton;
	Button* m_DownButton;
	Button* m_EnterButton;

};
#endif
