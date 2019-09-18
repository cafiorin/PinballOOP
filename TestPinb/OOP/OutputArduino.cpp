/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* BSD 3-Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef ARDUINOLIB
#include <Arduino.h>
#endif

#include "OutputArduino.h"
#include "Pinball.h"

//-------------------------------------------------------//
OutputArduino::OutputArduino(uint8_t port):Port(port)
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("OutputArduino Constructor"));
	#endif

	m_TimerOn = new Timer(100, this, TimerType::once);
	
	#ifdef ARDUINOLIB
	pinMode(port, OUTPUT);
	#endif

}

//-------------------------------------------------------//
OutputArduino::~OutputArduino()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGESCREATION
	LogMessage(F("OutputArduino Destructor"));
	#endif

	//delete m_TimerOn;
}

//-------------------------------------------------------//
bool OutputArduino::Init()
//-------------------------------------------------------//
{
	#ifdef DEBUGMESSAGES
	LogMessage(F("OutputArduino::Init"));
	#endif

	TurnOff();
	return true;
}

//-------------------------------------------------------//
void OutputArduino::TurnOn()
//-------------------------------------------------------//
{
	if(m_Enabled)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("OutputArduino::TurnOn"));
		#endif

		m_turnOn = true;
		#ifdef ARDUINOLIB
		digitalWrite(m_portNumber,HIGH);
		#endif
	}
}

//-------------------------------------------------------//
void OutputArduino::TurnOnByTimer(unsigned long time)
//-------------------------------------------------------//
{
	if (m_Enabled)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("OutputArduino::TurnOnByTime"));
		#endif

		m_TimerOn->ChangeTimerValue(time);
		m_TimerOn->Start();
		TurnOn();
	}
}

//-------------------------------------------------------//
bool OutputArduino::NotifyEvent(Object * /*sender*/, uint8_t event, uint8_t /*value*/)
//-------------------------------------------------------//
{
    #ifdef DEBUGMESSAGES
    LogMessage(F("OutputArduino::NotifyEvent"));
    #endif

	if (event == EVENT_TIMEISOVER)
	{
		TurnOff();
		return true;
	}

	return false;
}

//-------------------------------------------------------//
void OutputArduino::TurnOff()
//-------------------------------------------------------//
{
	if(m_Enabled)
	{
		#ifdef DEBUGMESSAGES
		LogMessage(F("OutputArduino::TurnOff"));
		#endif

		m_turnOn = false;
		#ifdef ARDUINOLIB
		digitalWrite(m_portNumber, LOW);
		#endif
	}
}
