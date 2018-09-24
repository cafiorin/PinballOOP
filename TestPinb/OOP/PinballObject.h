/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PinballObject__INCLUDED_
#define PinballObject__INCLUDED_

#include "defines.h"
#include "Object.h"

class Pinball;

class PinballObject : public Object
{
public:
	PinballObject(bool AddToListPinball=true);
	virtual ~PinballObject();

	bool IsEnabled() { return m_Enabled; }
	void Enable() { m_Enabled = true; }
	void Disable() { m_Enabled = false; }

	//virtual methods
	virtual bool Init();
	virtual void Loop();

protected:
	bool m_Enabled;
	bool m_AddToListPinball;
};

#endif
