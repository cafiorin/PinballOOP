/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Object__INCLUDED_
#define Object__INCLUDED_

#include "defines.h"
class HardwareSerial;
class Pinball;
class Event;

class Object
{
public:
	Object();
	virtual ~Object() {};

	int getId() { return m_Id; }

	void LogMessage(const __FlashStringHelper *szMessage);
	virtual bool NotifyEvent(Object *sender, Event *event);

	bool operator==(Object& Obj) 
	{ 
		if(&Obj != NULL)
			return (Obj.m_Id == static_cast<const Object&>(*this).m_Id);
	}

	bool operator!=(const Object& Obj) 
	{ 
		return !(Obj.m_Id != static_cast<const Object&>(*this).m_Id); 
	}

protected:
	int m_Id;
	static HardwareSerial *m_Serial;
	static Pinball *m_Pinball;

private:
	static int m_Ids;
};

#endif
