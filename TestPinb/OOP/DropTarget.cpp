/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DropTarget.h"

//-------------------------------------------------------//
DropTarget::DropTarget(const char *szName, Pinball *pinball, 
						int portNumberInput1, 
						int portNumberInput2, 
						int portNumberInput3, 
						int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTarget Constructor");
#endif

	m_sizeInputs = 3;
	m_input[0] = new Input("DT31In", pinball, portNumberInput1,this);
	m_input[1] = new Input("DT32In", pinball, portNumberInput2, this);
	m_input[2] = new Input("DT33In", pinball, portNumberInput3, this);

	m_output = new Output("DT3Out", pinball, portNumberOutput);

	Init();
}

//-------------------------------------------------------//
DropTarget::DropTarget(const char *szName, Pinball *pinball,
	int portNumberInput1,
	int portNumberInput2,
	int portNumberInput3,
	int portNumberInput4,
	int portNumberInput5,
	int portNumberOutput) : PinballObject(szName, pinball)
	//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTarget Constructor");
#endif

	m_sizeInputs = 5;
	m_input[0] = new Input("DT51In", pinball, portNumberInput1, this);
	m_input[1] = new Input("DT52In", pinball, portNumberInput2, this);
	m_input[2] = new Input("DT53In", pinball, portNumberInput3, this);
	m_input[3] = new Input("DT54In", pinball, portNumberInput4, this);
	m_input[4] = new Input("DT55In", pinball, portNumberInput5, this);

	m_output = new Output("DT5Out", pinball, portNumberOutput);

	Init();
}


//-------------------------------------------------------//
DropTarget::~DropTarget()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTarget Destructor");
#endif

	for (int i = 0; i < m_sizeInputs; i++)
	{
		delete m_input[i];
	} 

	delete m_output;
}

//-------------------------------------------------------//
bool DropTarget::Init()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTarget::Init");
#endif
	
	Reset();
	return false;
}

//-------------------------------------------------------//
bool DropTarget::Loop(int value)
//-------------------------------------------------------//
{
	if (m_enabled)
	{
		#ifdef DEBUGMESSAGESLOOP
		Debug("DropTarget::Loop");
		#endif

		bool allTargets = false;
		for (int i = 0; i < m_sizeInputs; i++)
		{
			if (m_input[i]->GetInput())
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
void DropTarget::Reset()
//-------------------------------------------------------//
{
#ifdef DEBUGMESSAGES
	Debug("DropTarget::Reset");
#endif

	m_AllTargets = false;
	m_output->TurnOnByTimer(TIME_COIL_ON);
}