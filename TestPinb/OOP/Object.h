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

class Object
{
public:
	Object();
	virtual ~Object() {};

#ifdef DEBUGMESSAGES

	int getId() { return m_Id; }
	bool operator==(Object& Obj)
	{
		if (&Obj != NULL)
			return (Obj.m_Id == static_cast<const Object&>(*this).m_Id);
	}

	bool operator!=(const Object& Obj)
	{
		return !(Obj.m_Id != static_cast<const Object&>(*this).m_Id);
	}

	void LogMessage(const __FlashStringHelper *szMessage);
	void LogMessageToConstChar(const char *szMessage);

#endif // DEBUGMESSAGES


	virtual bool NotifyEvent(Object *sender, uint8_t event, uint8_t value);


protected:
#ifdef DEBUGMESSAGES
	uint8_t m_Id;
#endif
	static HardwareSerial *m_Serial;
	static Pinball *m_Pinball;

#ifdef DEBUGMESSAGES
private:
	static uint8_t m_Ids;
#endif
};

#endif
