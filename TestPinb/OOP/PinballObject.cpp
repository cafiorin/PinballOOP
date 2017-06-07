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


#include "PinballObject.h"
#include "Pinball.h"

/*---------------------------------------------------------------------*/
PinballObject::PinballObject(const char *szName, Pinball *pinball)
/*---------------------------------------------------------------------*/
{
	strcpy(m_szName, szName);
	m_enabled = true;
	m_pinball = pinball;
	
	#ifdef DEBUGMESSAGES
	Debug("PinballObject Constructor");
	#endif

	if(m_pinball != NULL)
		m_pinball->AddPinballObject(this);
}

/*---------------------------------------------------------------------*/
PinballObject::~PinballObject()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("PinballObject Destructor");
	#endif

}


/*---------------------------------------------------------------------*/
void PinballObject::LogMessage(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	char szMsg[50];
	sprintf(szMsg, "[%s]:%s", m_szName, szMessage);
	
	if (m_pinball != NULL)
		m_pinball->LogMessage(szMsg);
}

/*---------------------------------------------------------------------*/
void PinballObject::Debug(const char *szMessage)
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	LogMessage(szMessage);
	#endif // DEBUGMESSAGES
}

/*---------------------------------------------------------------------*/
bool PinballObject::Init()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("PinballObject::Init");
	#endif

	return true;
}

/*---------------------------------------------------------------------*/
bool PinballObject::Loop()
/*---------------------------------------------------------------------*/
{
	#ifdef DEBUGMESSAGES
	Debug("PinballObject::Loop");
	#endif

	return false;
}

