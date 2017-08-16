/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DropTargetWithRemoteInput.h"

//-------------------------------------------------------//
DropTargetWithRemoteInput::DropTargetWithRemoteInput(const char *szName, Pinball *pinball, 
						int portNumberInput1, 
						int portNumberInput2, 
						int portNumberInput3, 
						int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTargetWithRemoteInput Constructor");
#endif

	m_sizeInputs = 3;
	m_input[0] = new RemoteInput("RDT31In", pinball, portNumberInput1);
	m_input[1] = new RemoteInput("RDT32In", pinball, portNumberInput2);
	m_input[2] = new RemoteInput("RDT33In", pinball, portNumberInput3);

	m_output = new Output("DT3Out", pinball, portNumberOutput);

	Init();
}

//-------------------------------------------------------//
DropTargetWithRemoteInput::DropTargetWithRemoteInput(const char *szName, Pinball *pinball,
	int portNumberInput1,
	int portNumberInput2,
	int portNumberInput3,
	int portNumberInput4,
	int portNumberInput5,
	int portNumberOutput) : PinballObject(szName, pinball)
	//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTargetWithRemoteInput Constructor");
#endif

	m_sizeInputs = 5;
	m_input[0] = new RemoteInput("RDT51In", pinball, portNumberInput1);
	m_input[1] = new RemoteInput("RDT52In", pinball, portNumberInput2);
	m_input[2] = new RemoteInput("RDT53In", pinball, portNumberInput3);
	m_input[3] = new RemoteInput("RDT54In", pinball, portNumberInput4);
	m_input[4] = new RemoteInput("RDT55In", pinball, portNumberInput5);

	m_output = new Output("DT5Out", pinball, portNumberOutput);

	Init();
}


//-------------------------------------------------------//
DropTargetWithRemoteInput::~DropTargetWithRemoteInput()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTargetWithRemoteInput Destructor");
#endif

	for (int i = 0; i < m_sizeInputs; i++)
	{
		delete m_input[i];
	} 

	delete m_output;
}

//-------------------------------------------------------//
bool DropTargetWithRemoteInput::Init()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTargetWithRemoteInput::Init");
#endif
	
	Reset();
	return false;
}

//-------------------------------------------------------//
bool DropTargetWithRemoteInput::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("DropTargetWithRemoteInput::Loop");
		#endif

		bool allTargets = false;
		for (int i = 0; i < m_sizeInputs; i++)
		{
			if (m_input[i]->GetRemoteInput())
			{
				allTargets = true;
			}
			else
			{
				allTargets = false;
				break;
			}
		}

		if (allTargets)
		{
			Reset();
		}

		return (allTargets);
	}

	return false;
}

//-------------------------------------------------------//
void DropTargetWithRemoteInput::Reset()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTargetWithRemoteInput::Reset");
#endif

	m_AllTargets = false;

	for (int i = 0; i < m_sizeInputs; i++)
	{
		m_input[i]->EmulateRemoteInput(false);
	}

	m_output->TurnOnByTimer(TIME_COIL_ON);
}