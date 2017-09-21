/* BSD 3 - Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(Menu__INCLUDED_)
#define Menu__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "PinballObject.h"

class Menu : public PinballObject
{
public:
	Menu(const char *szName, Pinball *pinball);
	virtual ~Menu();
	virtual bool Init();
	virtual bool Loop(int value);

protected:
	#ifdef DOS
	#endif
	
	#ifdef ARDUINO
	#endif

	void StartMenu();
	char* GetMenuLine1();
	char* GetMenuLine2();
	void PrintMenu();
	void GetNextOption();
	void GetPrevOption();

	bool m_isShowing;
	int m_option;
	int m_subOption;
};
#endif // !defined(Menu__INCLUDED_)
