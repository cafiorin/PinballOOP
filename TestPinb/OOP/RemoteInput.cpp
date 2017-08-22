/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "RemoteInput.h"

//-------------------------------------------------------//
RemoteInput::RemoteInput(const char *szName, Pinball *pinball, int portNumber):Port(pinball,szName,portNumber)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("RemoteInput Constructor");
	#endif

	m_emulateRemoteInput = false;
	m_portNumber = portNumber;
	Init();
}

//-------------------------------------------------------//
RemoteInput::~RemoteInput()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("RemoteInput Destructor");
	#endif
}

//-------------------------------------------------------//
bool RemoteInput::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("RemoteInput::Init");
	#endif

	m_emulateRemoteInput = false;
	return true;
}

//-------------------------------------------------------//
bool RemoteInput::CheckEdgePositive()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESLOOP
	Debug("RemoteInput::GetRemoteInput");
	#endif
	
	bool lastValue = m_emulateRemoteInput;
	m_emulateRemoteInput = false;
	return (lastValue);
}

//-------------------------------------------------------//
bool RemoteInput::Loop(int value)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGESLOOP
	Debug("RemoteInput::Loop");
#endif

	return false;
}
