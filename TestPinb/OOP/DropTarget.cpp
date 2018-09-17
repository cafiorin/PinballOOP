/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Pinball.h"
#include "DropTarget.h"
#include "Output.h"
#include "Event.h"
#include "SequencerLeds.h"

//-------------------------------------------------------//
DropTarget::DropTarget( 
						uint8_t portNumberInput1, 
						uint8_t portNumberInput2, 
						uint8_t portNumberInput3, 
						uint8_t portNumberOutput) : PinballObject()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("DropTarget Constructor"));
	#endif

	m_SequencerLeds = new SequencerLeds(SequencerType::blinkingAll, 300);
	m_SequencerLeds->Disable();

	m_sizeInputs = 3;
	m_input[0] = new Input(portNumberInput1,this);
	m_input[1] = new Input(portNumberInput2, this);
	m_input[2] = new Input(portNumberInput3, this);

	m_output = new Output(portNumberOutput);
}

//-------------------------------------------------------//
DropTarget::DropTarget(
	uint8_t portNumberInput1,
	uint8_t portNumberInput2,
	uint8_t portNumberInput3,
	uint8_t portNumberInput4,
	uint8_t portNumberInput5,
	uint8_t portNumberOutput) : PinballObject()
	//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("DropTarget Constructor"));
	#endif

	m_SequencerLeds = new SequencerLeds(SequencerType::blinkingAll, 300);
	m_SequencerLeds->Disable();

	m_sizeInputs = 5;
	m_input[0] = new Input(portNumberInput1, this);
	m_input[1] = new Input(portNumberInput2, this);
	m_input[2] = new Input(portNumberInput3, this);
	m_input[3] = new Input(portNumberInput4, this);
	m_input[4] = new Input(portNumberInput5, this);

	m_output = new Output(portNumberOutput);
}


//-------------------------------------------------------//
DropTarget::~DropTarget()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("DropTarget Destructor"));
	#endif

	delete m_SequencerLeds;

	for (uint8_t i = 0; i < m_sizeInputs; i++)
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
	LogMessage(F("DropTarget::Init"));
	#endif

	if (m_Pinball->GetStatus() == StatusPinball::playingmode)
	{
		Reset();
	}
	return true;
}

//-------------------------------------------------------//
void DropTarget::AddLeds(uint8_t led1, uint8_t led2, uint8_t led3)
//-------------------------------------------------------//
{
	m_SequencerLeds->AddLed(led1);
	m_SequencerLeds->AddLed(led2);
	m_SequencerLeds->AddLed(led3);
}

//-------------------------------------------------------//
void DropTarget::AddLeds(uint8_t led1, uint8_t led2, uint8_t led3, uint8_t led4, uint8_t led5)
//-------------------------------------------------------//
{
	m_SequencerLeds->AddLed(led1);
	m_SequencerLeds->AddLed(led2);
	m_SequencerLeds->AddLed(led3);
	m_SequencerLeds->AddLed(led4);
	m_SequencerLeds->AddLed(led5);

}

//-------------------------------------------------------//
bool DropTarget::NotifyEvent(Object *sender, Event *event)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("DropTarget::NotifyEvent"));
	#endif

	if (event->GetIdEvent() == EVENT_EDGEPOSITIVE)
	{
		uint8_t totalTargets = 0;
		for (uint8_t i = 0; i < m_sizeInputs; i++)
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
			m_Pinball->NotifyEvent(this, &Event(EVENT_DROPTARGETDOWN));
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
	LogMessage(F("DropTarget::Reset"));
	#endif

	m_AllTargets = false;
	m_output->TurnOnByTimer(TIME_COIL_ON);
	m_SequencerLeds->Start();
}