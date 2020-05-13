#ifndef Door__INCLUDED_
#define Door__INCLUDED_

class Button;

class Door
{
public:
	Door();
	~Door();

private:
	Button* m_MenuButton;
	Button* m_UpButton;
	Button* m_DownButton;
	Button* m_EnterButton;

};
#endif
