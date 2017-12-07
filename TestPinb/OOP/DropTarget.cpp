/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DropTarget.h"
#include "Output.h"
#include "PinballMaster.h"
#include "SequencerLeds.h"

//-------------------------------------------------------//
DropTarget::DropTarget(const char *szName, PinballMaster *pinball, 
						int portNumberInput1, 
						int portNumberInput2, 
						int portNumberInput3, 
						int portNumberOutput) : PinballObject(szName, pinball)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("DropTarget Constructor");
	#endif

	m_SequencerLeds = new SequencerLeds(m_pinball, SequencerType::blinkingAll, 300);
	m_SequencerLeds->Disable();

	m_sizeInputs = 3;
	m_input[0] = new Input("DT31In", pinball, portNumberInput1,this);
	m_input[1] = new Input("DT32In", pinball, portNumberInput2, this);
	m_input[2] = new Input("DT33In", pinball, portNumberInput3, this);

	m_output = new Output("DT3Out", pinball, portNumberOutput);
}

//-------------------------------------------------------//
DropTarget::DropTarget(const char *szName, PinballMaster *pinball,
	int portNumberInput1,
	int portNumberInput2,
	int portNumberInput3,
	int portNumberInput4,
	int portNumberInput5,
	int portNumberOutput) : PinballObject(szName, pinball)
	//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("DropTarget Constructor");
	#endif

	m_SequencerLeds = new SequencerLeds(m_pinball, SequencerType::blinkingAll, 300);
	m_SequencerLeds->Disable();

	m_sizeInputs = 5;
	m_input[0] = new Input("DT51In", pinball, portNumberInput1, this);
	m_input[1] = new Input("DT52In", pinball, portNumberInput2, this);
	m_input[2] = new Input("DT53In", pinball, portNumberInput3, this);
	m_input[3] = new Input("DT54In", pinball, portNumberInput4, this);
	m_input[4] = new Input("DT55In", pinball, portNumberInput5, this);

	m_output = new Output("DT5Out", pinball, portNumberOutput);
}


//-------------------------------------------------------//
DropTarget::~DropTarget()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Debug("DropTarget Destructor");
	#endif

	delete m_SequencerLeds;

	for (int i = 0; i < m_sizeInputs; i++)
	{
		delete m_input[i];
	} 

	delete m_output;
}

//-------------------------------------------------------//
bool DropTarget::Init(StatusPinball status)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("DropTarget::Init");
	#endif
	if (status == StatusPinball::playingmode)
	{
		Reset();
	}
	return true;
}

//-------------------------------------------------------//
void DropTarget::AddLeds(int led1, int led2, int led3)
//-------------------------------------------------------//
{
	m_SequencerLeds->AddLed(led1);
	m_SequencerLeds->AddLed(led2);
	m_SequencerLeds->AddLed(led3);
}

//-------------------------------------------------------//
void DropTarget::AddLeds(int led1, int led2, int led3, int led4, int led5)
//-------------------------------------------------------//
{
	m_SequencerLeds->AddLed(led1);
	m_SequencerLeds->AddLed(led2);
	m_SequencerLeds->AddLed(led3);
	m_SequencerLeds->AddLed(led4);
	m_SequencerLeds->AddLed(led5);

}

//-------------------------------------------------------//
bool DropTarget::NotifyEvent(PinballObject *sender, int event, int valueToSend)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Debug("DropTarget::NotifyEvent");
	#endif

	if (event == EVENT_EDGEPOSITIVE)
	{
		int totalTargets = 0;
		for (int i = 0; i < m_sizeInputs; i++)
		{
			if (m_input[i]->GetInput())
			{
				m_SequencerLeds->TurnOnAlwaysLed(i, true);
				totalTargets++;
			}
			else
			{
				m_SequencerLeds->TurnOnAlwaysLed(i, false);
			}
		}

		if (totalTargets == m_sizeInputs)
		{
			m_pinball->NotifyEvent(this, EVENT_DROPTARGETDOWN, m_sizeInputs);
			//Reset();
			return true;
		}
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
	m_SequencerLeds->Start();
}