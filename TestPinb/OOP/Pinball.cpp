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


#include "Pinball.h"
#include "PinballObject.h"
#include "HardwareSerial.h"
#include "Vector.h"

/*---------------------------------------------------------------------*/
Pinball::Pinball(const char *szName, HardwareSerial *serial, bool master)
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_master = master;
	m_serial = serial;
	
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Constructor");
	#endif
}

/*---------------------------------------------------------------------*/
Pinball::~Pinball()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball Destructor");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		delete m_PinballObjs[i];
	}

}

/*---------------------------------------------------------------------*/
void Pinball::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	m_serial->println(szMessage);
	#endif
}

/*---------------------------------------------------------------------*/
void Pinball::AddPinballObject(PinballObject *Pinballobj)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::AddPinballObject");
	#endif

	m_PinballObjs.push_back(Pinballobj);
}

/*---------------------------------------------------------------------*/
void Pinball::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::Init");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Init();
	}
}


/*---------------------------------------------------------------------*/
void Pinball::Loop()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage("Pinball::Loop");
	#endif

	for (unsigned int i = 0; i < m_PinballObjs.size(); i++)
	{
		m_PinballObjs[i]->Loop();
	}
}
