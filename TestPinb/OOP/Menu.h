/* BSD 3 - Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Menu__INCLUDED_)
#define Menu__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Pinball.h"
#include "Vector.h"

enum ButtonPressed
{
	start,
	up,
	down,
	enter
};

#define MAX_NAME_MENU 10

class MenuString
{
public:
	MenuString(MenuString *parent, uint8_t action, char *szMenu)
	{
		if(strlen(szMenu) < MAX_NAME_MENU)
			strcpy(m_szMenu, szMenu);
		else
			strcpy(m_szMenu, "MAX");

		m_action = action;
		m_parent = parent;
		if (parent != NULL)
		{
			parent->AddChild(this);
		}
	}

	void AddChild(MenuString *menustring)
	{
		m_Children.push_back(menustring);
	}

	char *GetString() { return m_szMenu; }
	Vector<MenuString *>GetChildren() { return m_Children; }
	uint8_t GetAction() { return m_action; }
	MenuString *GetParent() { return m_parent; }

private:
	MenuString *m_parent;
	uint8_t m_action;
	char m_szMenu[MAX_NAME_MENU];
	Vector<MenuString *> m_Children;
};

class Menu : public PinballObject
{
public:
	Menu();
	virtual ~Menu();
	bool Init();
	void DestroyChildren(MenuString *menuString);

	void PressButtonMenu();
	bool PressUpDownButton(bool upButton);
	void PressButtonEnter();

protected:
	MenuString *m_pMenu;
	void PrintMenu(ButtonPressed button);

	bool m_isShowing;
	MenuString *m_menuOptionSelected;
	uint8_t m_subOption;
	MenuString *m_subOptionSelected;
	bool m_backSelected;
};
#endif // !defined(Menu__INCLUDED_)
