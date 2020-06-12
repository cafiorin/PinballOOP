/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DropTarget.h"
#include "Observer.h"
#include "BitOutput.h"
#include "BitInput.h"
#include "SequencerLeds.h"
#include "Initializable.h"
#include "EventType.h"
#include "Subject.h"
#include "Logger.h"
#include "ChangeableStatus.h"

//-------------------------------------------------------//
DropTarget::DropTarget(BitInput* input1, BitInput* input2, BitInput* input3,
					   BitOutput* output, LedControl* ledControl) : Observer(), Initializable(), ChangeableStatus()
//-------------------------------------------------------//
{
	Initialize(3, input1, input2, input3, NULL, NULL, output, ledControl);
}

//-------------------------------------------------------//
DropTarget::DropTarget(	BitInput* input1,BitInput* input2, BitInput* input3,
	BitInput* input4,BitInput* input5,BitOutput* output, LedControl* ledControl) : Observer(), Initializable(), ChangeableStatus()
//-------------------------------------------------------//
{
	Initialize(5, input1, input2, input3, input4, input5, output, ledControl);
}

//-------------------------------------------------------//
void DropTarget::Initialize(byte sizeInputs,BitInput* input1,BitInput* input2,BitInput* input3,
	BitInput* input4,BitInput* input5,BitOutput* output, LedControl* ledControl)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("DropTarget Constructor"));
	#endif

	m_EventToDropTargetComplete = NULL;

	m_SequencerLeds = new SequencerLeds(SequencerType::blinkingAll, 300, ledControl);

	m_sizeInputs = sizeInputs;
	m_input[0] = input1;
	m_input[1] = input2;
	m_input[2] = input3;
	m_input[3] = input4;
	m_input[4] = input5;

	for (byte i = 0; i < m_sizeInputs; i++)
		m_input[i]->AddObserverToEdgePositive(this);

	m_output = output;

}


//-------------------------------------------------------//
DropTarget::~DropTarget()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	Logger::LogMessage(F("DropTarget Destructor"));
	#endif

	delete m_SequencerLeds;
	delete m_EventToDropTargetComplete;
}

//-------------------------------------------------------//
void DropTarget::init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("DropTarget::Init"));
	#endif

	Reset();
}

//-------------------------------------------------------//
void DropTarget::AddLeds(byte led1, byte led2, byte led3)
//-------------------------------------------------------//
{
	m_SequencerLeds->AddLed(led1);
	m_SequencerLeds->AddLed(led2);
	m_SequencerLeds->AddLed(led3);
}

//-------------------------------------------------------//
void DropTarget::AddLeds(byte led1, byte led2, byte led3, byte led4, byte led5)
//-------------------------------------------------------//
{
	m_SequencerLeds->AddLed(led1);
	m_SequencerLeds->AddLed(led2);
	m_SequencerLeds->AddLed(led3);
	m_SequencerLeds->AddLed(led4);
	m_SequencerLeds->AddLed(led5);

}

//-------------------------------------------------------//
void DropTarget::onNotifySubject(EventType event, byte /*value*/)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("DropTarget::NotifyEvent"));
	#endif

	if (event == EventType::EdgePositive)
	{
		byte totalTargets = 0;
		for (byte i = 0; i < m_sizeInputs; i++)
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
			if (m_EventToDropTargetComplete != NULL)
			{
				m_EventToDropTargetComplete->notifyObserver();
			}
			else
			{
				Reset();
			}
		}
	}
}


//-------------------------------------------------------//
void DropTarget::Reset()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	Logger::LogMessage(F("DropTarget::Reset"));
	#endif

	m_AllTargets = false;
	m_output->Pulse();
}

//------------------------------------------------//
void DropTarget::AddObserverToDropTargeComplete(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToDropTargetComplete == NULL)
	{
		m_EventToDropTargetComplete = new Subject(EventType::DropTargetComplete, m_sizeInputs);
	}

	m_EventToDropTargetComplete->registerObserver(observer);
}

//-------------------------------------------------------//
void DropTarget::changeStatus(StatusPinballMachine status)
//-------------------------------------------------------//
{
	if (status == StatusPinballMachine::initplaymode)
	{
		Reset();
	}
	else if (status == StatusPinballMachine::playingmode)
	{
		m_SequencerLeds->Start();
	}

}

