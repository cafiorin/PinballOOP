/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PinballObject.h"
#include "Object.h"
#include "Pinball.h"
#include "Utils.h"

/*---------------------------------------------------------------------*/
PinballObject::PinballObject() : Object()
/*---------------------------------------------------------------------*/
{
	m_Enabled = true;

	if (m_Pinball != NULL)
	{
		m_Pinball->AddPinballObject(this);
	}
}

/*---------------------------------------------------------------------*/
PinballObject::~PinballObject()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("PinballObject Destructor"));
	#endif

	if (m_Pinball != NULL)
		m_Pinball->RemovePinballObject(this);
}

/*---------------------------------------------------------------------*/
bool PinballObject::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("PinballObject::Init"));
	#endif

	return true;
}

/*---------------------------------------------------------------------*/
void PinballObject::Loop()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGESLOOP
	LogMessage(F("PinballObject::Loop"));
	#endif
}

