#include "BitOutput.h"
#include "Subject.h"
#include "NewTimer.h"
#include "LatchOutputs.h"

#include "..\\OOP\\Utils.h"
#include "..\\OOP\\defines.h"

//-------------------------------------------------------//
BitOutput::BitOutput(LatchOutputs *latch, byte port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("BitOutput Constructor"));
	#endif
	
	m_portNumber = port;
	m_LatchOutputs = latch;

	m_TimerOn = new NewTimer(100, NewTimerType::once);
	m_TimerOn->AddObserverToTimeIsOver(this);
}

//-------------------------------------------------------//
void BitOutput::init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("BitOutput::Init"));
	#endif

	TurnOff();
}

//------------------------------------------------//
void BitOutput::AddObserverToTurnOn(Observer* observer)
//------------------------------------------------//
{
	if (m_EventToTurnOn == NULL)
	{
		m_EventToTurnOn = new Subject(EventType::TurnOn, m_portNumber);
	}

	m_EventToTurnOn->registerObserver(observer);
}


//-------------------------------------------------------//
void BitOutput::TurnOnByDelay(unsigned long time)
//-------------------------------------------------------//
{
	TurnOn();
	delay(time);
	TurnOff();
}

//-------------------------------------------------------//
void BitOutput::TurnOn()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("BitOutput::TurnOn"));
	#endif

	m_turnOn = true;
	m_LatchOutputs->writeChannelLatch(m_portNumber, HIGH);
}

//-------------------------------------------------------//
void BitOutput::TurnOnByTimer(unsigned long time)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("BitOutput::TurnOnByTime"));
	#endif

	m_TimerOn->ChangeTimerValue(time);
	m_TimerOn->Start();
	TurnOn();
}

//-------------------------------------------------------//
void BitOutput::onNotifySubject(const Subject*, EventType event, byte value)
//-------------------------------------------------------//
{
    #ifdef DEBUGMESSAGES
    LogMessage(F("BitOutput::NotifyEvent"));
    #endif

	if (event == EventType::TimeIsOver)
	{
		TurnOff();
	}
}

//-------------------------------------------------------//
void BitOutput::TurnOff()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("BitOutput::TurnOff"));
	#endif

	m_turnOn = false;
	m_LatchOutputs->writeChannelLatch(m_portNumber, LOW);
}
