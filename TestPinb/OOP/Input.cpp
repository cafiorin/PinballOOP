/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Code by Cassius Fiorin - cafiorin@gmail.com
 http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Input.h"

//-------------------------------------------------------//
Input::Input(Pinball *pinball, const char *szName, int portNumber):Port(pinball,szName,portNumber)
//-------------------------------------------------------//
{
	m_debounceDelay=50;
}

//-------------------------------------------------------//
Input::~Input()
//-------------------------------------------------------//
{
}

//-------------------------------------------------------//
bool Input::Init()
//-------------------------------------------------------//
{
	#ifdef ARDUINO
	pinMode(m_portNumber, INPUT);
	#endif

	m_startReading = false;
	m_lastState = CheckPort();
	m_lastDebounceTime = Millis();

	return true;
}

//-------------------------------------------------------//
bool Input::CheckPort()
//-------------------------------------------------------//
{
	#ifdef ARDUINO
	return (digitalRead(m_portNumber) == LOW);
	#endif

	#ifdef DOS
	return true;
	#endif
}

//-------------------------------------------------------//
bool Input::CheckEdgePositive()
//-------------------------------------------------------//
{
  bool edge = false;
  if(m_enabled)
  {
	  bool reading = CheckPort();

	  // If the switch changed, due to noise or pressing:
	  if (reading != m_lastState && reading == true && m_lastState == false) 
	  {
		// reset the debouncing timer
		m_lastDebounceTime = Millis();
		m_startReading = true;
	  }

	  if (m_startReading && ((Millis() - m_lastDebounceTime) > m_debounceDelay)) 
	  {
		// if the button state has changed:
		if (reading == true) 
		{
			edge = true;
		}
		m_startReading = false;
	  }

	  m_lastState = reading;
  }
  return edge;
}

