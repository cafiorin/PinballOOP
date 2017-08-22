/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(_RemoteInput__INCLUDED_)
#define _RemoteInput__INCLUDED_

#include "defines.h"
#include "Utils.h"
#include "Port.h"
#include "Timer.h"

class RemoteInput : public Port
{

public:
	RemoteInput(const char *szName, Pinball *pinball, int portNumber);
	virtual ~RemoteInput();
	bool CheckEdgePositive();

	virtual bool Init();
	virtual bool Loop(int value);

	void EmulateRemoteInput(bool value) 
	{ 
		#ifdef DEBUGMESSAGES
		LogMessage("RemoteInput EmulateRemoteInput");
		#endif

		m_emulateRemoteInput = value; 
	}

	bool GetRemoteInput() { return m_emulateRemoteInput; }
	int GetPortNumber() { return m_portNumber; }

private:
	bool m_emulateRemoteInput;
};
#endif // !defined(_RemoteInput__INCLUDED_)
