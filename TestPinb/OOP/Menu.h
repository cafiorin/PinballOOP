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

	char* GetMenuLine1();
	char* GetMenuLine2();

};
#endif // !defined(Menu__INCLUDED_)
